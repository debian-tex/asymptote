#!/usr/bin/env python3
__doc__ = """
Determine package version information from configure.ac file for Asymptote
"""
__author__ = "Supakorn 'Jamie' Rassameemasmuang <jamievlin@outlook.com>"

import pathlib
import re

REGEXES = {
    "base": re.compile(
        r"AC_INIT\(\s*\[\s*(.+)\s*]\s*,"  # pkg name
        + r"\s*\[\s*(.+)\s*]\s*,"  # pkg version
        + r"\s*\[\s*(.+)\s*]\s*\)"  # issue url
    ),
    "asygl": re.compile(r"ASYGLVERSION\s*=\s*(.+)"),
}


def process_configure_ac_file(f):
    """
    Returns a dictionary containing version information, if found
    from the configure.ac file object
    """
    regexes_to_search = dict(REGEXES)
    result = {}
    for line in f:
        if not regexes_to_search:
            return result  # done now, can return
        regex_result = {key: val.match(line) for key, val in regexes_to_search.items()}
        regex_result_not_none: dict[str, re.Match[str]] = {
            key: val for key, val in regex_result.items() if val is not None
        }
        for key, match_obj in regex_result_not_none.items():
            regexes_to_search.pop(key)
            if key == "base":
                result.update(
                    {
                        "name": match_obj.group(1),
                        "version-base": match_obj.group(2),
                        "issue-url": match_obj.group(3),
                    }
                )
            if key == "asygl":
                result["asygl-version"] = match_obj.group(1)
    return result


def determine_asy_pkg_info(ac_file="configure.ac"):
    """
    Returns a dictionary containing version information, if found
    from the ac_file specified
    """
    with open(
        ac_file,
        "r",
        encoding="utf-8",
    ) as f:
        return process_configure_ac_file(f)


def main():
    pkg_version_info = determine_asy_pkg_info(
        pathlib.Path(__file__).parent / "configure.ac"
    )
    version_tuple = (
        pkg_version_info.get("name", "NAME-UNKNOWN"),
        pkg_version_info.get("version-base", "VERSION-UNKNOWN"),
        pkg_version_info.get("issue-url", "ISSUE-URL-UNKNOWN"),
        pkg_version_info.get("asygl-version", "ASYGL-UNKNOWN"),
    )
    print(";".join(version_tuple), end="")


if __name__ == "__main__":
    main()
