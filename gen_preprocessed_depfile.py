#!/usr/bin/env python3
import io
import json
import shlex
import subprocess as sp
import sys
import tempfile
from argparse import ArgumentParser
from typing import List, Optional


def execute_and_report_err(args: List[str], error_heading="Error"):
    try:
        return sp.run(
            args, stdout=sp.PIPE, stderr=sp.PIPE, universal_newlines=True, check=True
        )
    except sp.CalledProcessError as e:
        sys.stderr.write(f"{error_heading}\n")
        sys.stderr.write(e.stderr)
        sys.stderr.write(f"stdout:\n{e.stdout}")
        sys.stderr.write("\n")
        sys.stderr.flush()
        raise


def parse_args():
    args_parser = ArgumentParser()
    args_parser.add_argument(
        "--out-i-file", type=str, required=True, help="Output for preprocessed file"
    )

    args_parser.add_argument(
        "--out-dep-file",
        type=str,
        required=False,
        help="Location of output depfile. Optional when used with gcc. "
        + "If not given, will not output dep file",
    )

    args_parser.add_argument(
        "--in-src-file",
        type=str,
        required=True,
        help="Location of source file to process",
    )

    args_parser.add_argument(
        "--cxx-compiler", type=str, required=True, help="C++ compiler to use"
    )

    args_parser.add_argument("--msvc", action="store_true")

    args_parser.add_argument(
        "--include-dirs", type=str, help="Include directories separated by semicolon"
    )

    args_parser.add_argument(
        "--additional-raw-arguments",
        type=str,
        help="Additional arguments to pass to the compiler. "
        + "Only for use on UNIX systems",
    )

    args_parser.add_argument(
        "--macro-defs",
        type=str,
        help="Macro definitions in the form VALA=CONTENTA or VALB",
    )

    args_parser.add_argument(
        "--cxx-standard",
        type=str,
    )

    args_parser.add_argument(
        "--dep-file-only",
        action="store_true",
        help="If given, will only generate dependency file without preprocessed file."
        + "For gcc usage only.",
    )
    return args_parser.parse_args()


class CompileOptions:
    def __init__(
        self,
        compiler: str,
        include_dirs: Optional[List[str]] = None,
        macros: Optional[List[str]] = None,
        **kwargs,
    ):
        """
        :param compiler: C++ compiler to use for preprocessing
        :param include_dirs: List of include directories to pass to C++ compiler for
            preprocessing
        :param macros: List of macros to pass to the C++ compiler for preprocessing.
            Must be in 'MACRO' or 'MACRO=VALUE' form.
        :param kwargs: Accepts two extra arguments:
            - "extra_flags": Extra flags to pass to compiler for preprocessing
            - "standard": C++ standard to use.
            This is passed to the compiler as "-std=c++<standard>".
        """
        self._compiler = compiler
        self._include_dirs = include_dirs or []
        self._macros = macros or []
        self._extra_flags: List[str] = kwargs.get("extra_flags") or []
        self._standard: str = kwargs.get("standard") or "17"

    @property
    def compiler(self):
        return self._compiler

    def build_args_for_gcc(
        self,
        src_file: str,
        out_file: Optional[str],
        addr_flags: Optional[List[str]] = None,
    ):
        base_args = (
            [f"-I{include_dir}" for include_dir in self._include_dirs]
            + [f"-D{macro}" for macro in self._macros]
            + [f"-std=c++{self._standard}"]
            + self._extra_flags
        )

        if addr_flags:
            base_args.extend(addr_flags)

        if out_file:
            base_args.extend(["-o", out_file])

        base_args.append(src_file)
        return base_args

    def build_args_for_msvc(
        self,
        src_file: str,
        out_file: Optional[str],
        addr_flags: Optional[List[str]] = None,
    ):
        base_args = (
            [f"/I{include_dir}" for include_dir in self._include_dirs]
            + [f"/D{macro}" for macro in self._macros]
            + [f"/std:c++{self._standard}", "/Zc:__cplusplus"]
            + self._extra_flags
        )
        if addr_flags:
            base_args.extend(addr_flags)

        if out_file:
            base_args.extend(["/F", out_file])
        base_args.append(src_file)
        return base_args


def compile_for_depfile_gcc(
    compile_opt: CompileOptions, src_in: str, src_out: str, depfile_out: str
):
    args = [compile_opt.compiler] + compile_opt.build_args_for_gcc(
        src_in,
        None,
        ["-DDEPEND", "-DNOSYM", "-M", "-MG", "-O0", "-MT", src_out, "-MF", depfile_out],
    )
    try:
        sp.run(args, check=True, stdout=sp.PIPE, stderr=sp.PIPE, text=True)
    except sp.CalledProcessError as e:
        sys.stderr.write("Process stderr:\n")
        sys.stderr.write(e.stderr)
        sys.stderr.write("Process output:\n")
        sys.stderr.write(e.stdout)
        sys.stderr.flush()
        raise


def compile_for_preproc_gcc(compile_opt: CompileOptions, src_in: str, preproc_out: str):
    args = [compile_opt.compiler] + compile_opt.build_args_for_gcc(
        src_in, preproc_out, ["-E", "-DNOSYM"]
    )
    try:
        sp.run(args, check=True, stdout=sp.PIPE, stderr=sp.PIPE, text=True)
    except sp.CalledProcessError as e:
        sys.stderr.write("Process stderr:\n")
        sys.stderr.write(e.stderr)
        sys.stderr.write("Process out:\n")
        sys.stderr.write(e.stdout)
        sys.stderr.flush()
        raise


def escape_windows_path(raw_path: str) -> str:
    escape_chars = {" ", "$", "#"}
    with io.StringIO() as ret_str_io:
        for char in raw_path:
            if char in escape_chars:
                ret_str_io.write("\\")
            ret_str_io.write(char)
        return ret_str_io.getvalue()


def compile_for_preproc_and_depfile_msvc(
    compile_opt: CompileOptions, src_in: str, preproc_out: str, depfile_out: str
):
    with tempfile.TemporaryDirectory() as td:
        args = [compile_opt.compiler] + compile_opt.build_args_for_msvc(
            src_in,
            None,
            [
                "/DNOSYM",
                "/DDEPEND",
                "/P",
                f"/Fi{preproc_out}",
                "/sourceDependencies",
                f"{td}/srcdep.json",
            ],
        )
        execute_and_report_err(args, "MSVC Error")
        with open(f"{td}/srcdep.json", "r", encoding="utf-8") as fread:
            dep_data = json.load(fread)

    include_fil_str = " ".join(
        escape_windows_path(include_fil)
        for include_fil in dep_data["Data"].get("Includes", [])
    )

    with open(depfile_out, "w", encoding="utf-8") as depfile_writer:
        depfile_writer.write(escape_windows_path(preproc_out))
        depfile_writer.write(": ")
        depfile_writer.write(include_fil_str)


def main():
    args = parse_args()
    opt = CompileOptions(
        args.cxx_compiler,
        args.include_dirs.split(";") if args.include_dirs else None,
        args.macro_defs.split(";") if args.macro_defs else None,
        extra_flags=(
            shlex.split(args.additional_raw_arguments)
            if args.additional_raw_arguments
            else None
        ),
        standard=args.cxx_standard,
    )

    if args.msvc:
        compile_for_preproc_and_depfile_msvc(
            opt, args.in_src_file, args.out_i_file, args.out_dep_file
        )
    else:
        if not args.out_dep_file and args.dep_file_only:
            raise RuntimeError("Dependency file output must be given")
        if args.out_dep_file:
            compile_for_depfile_gcc(
                opt, args.in_src_file, args.out_i_file, args.out_dep_file
            )
        if not args.dep_file_only:
            compile_for_preproc_gcc(opt, args.in_src_file, args.out_i_file)


if __name__ == "__main__":
    main()
