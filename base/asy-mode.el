;;; asy-mode.el

;; Copyright (C) 2006
;; Author: Philippe IVALDI 20 August 2006
;; Modified by: John Bowman 25 August 2006
;; Last modification: 01 September 2006 (John Bowman)
;;
;; This program is free software ; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation ; either version 2 of the License, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful, but
;; WITHOUT ANY WARRANTY ; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
;; General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program ; if not, write to the Free Software
;; Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

;; Emacs mode for editing Asymptote source code.

;; INSTALLATION:
;; Place this file (asy-mode.el) and asy-keywords.el in your Emacs load path.
;; Then choose ONE of the following installation methods:

;; * Method 1:
;;   Copy and uncomment the following lines to your .emacs initialization file:
;;(autoload 'asy-mode "asy-mode.el" "Asymptote major mode." t)
;;(autoload 'lasy-mode "asy-mode.el" "hybrid Asymptote/Latex major mode." t)
;;(autoload 'asy-insinuate-latex "asy-mode.el" "Asymptote insinuate LaTeX." t)
;;(add-to-list 'auto-mode-alist '("\\.asy$" . asy-mode))

;; * Method 2:
;;   Copy and uncomment the following line to your .emacs initialization file:
;;(require 'asy-mode)

;; Notes:
;; See also paragraph II of the documentation below to automate asy-insinuate-latex. 

;; For full functionality the two-mode-mode package should also be installed
;; (http://www.dedasys.com/freesoftware/files/two-mode-mode.el).
;; The package texmathp is optional.

;;;###autoload
(define-derived-mode asy-mode objc-mode "Asymptote"
  "Emacs mode for editing Asymptote source code.
For full functionality the 'two-mode-mode' package should also be installed
(http://www.dedasys.com/freesoftware/files/two-mode-mode.el).
The package 'texmathp' is optional.

I. This package provides two modes:
  1- asy-mode:
  All the files with the extension '.asy' are edited in this mode, which provides the following features:
  * Syntax color highlighting;
  * Compiling and viewing current buffer with the key binding C-c C-c;
  * Moving cursor to the error by pressing the key F4.
  * Showing the available function prototypes for the command at the cursor with the key binding C-c ?
  * Inserting template by pressing the key F3.
  - For example ife<F3> gives:
  if (*)
    {
      **
    }
  else
    {
      ***
    }

  The cursor is *. Press M-Right to go to **, M-Right again for ***
  - Look at the code after the comment 'Templates appended to asy-tempo-tags' to add your entries.
  * Compiling and viewing a TeX document linked with the current buffer (usually a document that includes the output picture).
  To link a Tex document try 'M-x asy-set-master-tex' follow by C-Return (see descriptions further of the key binding C-Return, C-S-Return, M-Return, M-S-Return etc within 2- lasy-mode)

  2- lasy-mode
  Editing a TeX file that contains Asymptote code is facilitated with the hybrid mode 'lasy-mode'.
  Toggle lasy-mode with M-x lasy-mode.
  In this hybrid mode the major mode is LaTeX when the cursor is in LaTeX code and becomes asy-mode when the cursor is between '\begin{asy}' and '\end{asy}'.
  All the features of asy-mode are provided and the key binding C-c C-c of asy-mode compiles and views only the code of the picture where is the cursor.
  Note that some keys binding are added to the LaTeX-mode-map in lasy-mode and also, if you want, in pure LaTeX-mode (customize the variable 'lasy-keep-key' to accept or refuse the modifications in pure LaTeX-mode).
  * C-return : compile (if the buffer/file is modified) and view the postscript output with sequence [latex->[asy->latex]->dvips]->PSviewer
  * M-return : same with pdf output and with the sequence [pdflatex -shell-escape->[asy->pdflatex -shell-escape]]->PDFviewer
  * C-M-return : same with pdf output and with the sequence [latex->[asy->latex]->dvips->ps2pdf]->PSviewer
  * Add the Shift key to the sequence of keys to compile even if the file is not modified.

II. To add a menu bar in current 'latex-mode' buffer and activate hot keys, use 'M-x asy-insinuate-latex <RET>'.
You can automate this feature for all the 'latex-mode' buffers by inserting the five following lines in your .emacs initialization file:
   (eval-after-load \"latex\"
     '(progn
        ;; Add here your personal features for 'latex-mode':
        (asy-insinuate-latex t) ;; Asymptote globally insinuates Latex.
        ))

You can access this help within Emacs by the key binding C-h f asy-mode <RET>

BUGS:
This package has been created and tested with:
- Linux Debian Sarge
- GNU Emacs 22.0.50.1
- AUCTeX 11.55
- Asymptote 1.13
Report bugs to http://asymptote.sourceforge.net

Some variables can be customized: M-x customize-group <RET> asymptote <RET>."

  (setq c++-font-lock-extra-types (cons "true" c++-font-lock-extra-types))

;;  (setq skeleton-pair t)
;; Next 3 lines disabled: end delimiters are treated as begin delimiters!
;;  (define-key asy-mode-map "\"" 'skeleton-pair-insert-maybe)
;;  (define-key asy-mode-map "\'" 'skeleton-pair-insert-maybe)
;;  (define-key asy-mode-map "\$" 'skeleton-pair-insert-maybe)
;; Next line disabled since this interferes with grouping existing code
;;  (define-key asy-mode-map "\{" 'skeleton-pair-insert-maybe)
;; Next 2 lines also disabled as they can make typing awkward.
;;  (define-key asy-mode-map "\(" 'skeleton-pair-insert-maybe)
;;  (define-key asy-mode-map "\[" 'skeleton-pair-insert-maybe)
)

(require 'font-lock)
(require 'cc-mode)

(add-to-list 'auto-mode-alist '("\\.asy$" . asy-mode))

;; Make asy-mode work with other shells.

(defcustom asy-command-location ""
  "*If not in the path, you can put here the name of the directory containing Asy's binary files.
this variable must end in / (UNIX) or \ (MSWindows)."
  :type 'directory
  :group 'asymptote)

(defcustom asy-temp-dir temporary-file-directory
  "*The name of a directory for Asy's temporary files.
Such files are generated by functions like
`asy-compile' when lasy-mode is enable."
  :type 'directory
  :group 'asymptote)

(defcustom ps-view-command (cond
                            ((eq window-system 'x)
                             "gv")
                            ((eq window-system 'w32)
                             "gsview")
                            (t "_indefinite_ps_viewer_"))
  "Command to view a Postscript file."
  :type 'file
  :group 'asymptote)

(defcustom pdf-view-command
  (cond
   ((eq window-system 'x)
    "xpdf")
   ((eq window-system 'w32)
    "acroread")
   (t "_indefinite_pdf_viewer"))
  "Command to view a Postscript file."
  :type 'file
  :group 'asymptote)

(defcustom lasy-keep-key t
  "*If on, keep the binding key of lasy-mode in all latex-mode.
The folowing keys are added:
\(kbd \"<M-return>\"\) `lasy-view-pdf-via-pdflatex\)
\(kbd \"<C-return>\"\) `lasy-view-ps\)
\(kbd \"<C-M-return>\"\) `lasy-view-pdf-via-ps2pdf\)"
  :type 'boolean
  :group 'asymptote)


(defvar asy-TeX-master-file nil
  "TeX file associate with current asymptote code.
This variable must be modified only using the function 'asy-set-master-tex by M-x asy-set-master-tex <RET>.")
(make-variable-buffer-local 'asy-TeX-master-file)

(defun asy-add-function-keywords (function-keywords face-name)
  (let* ((keyword-list (mapcar #'(lambda (x)
                                   (symbol-name  x))
                               function-keywords))
         (keyword-regexp (concat "\\<\\("
                                 (regexp-opt keyword-list)
                                 "\\)(")))
    (font-lock-add-keywords 'asy-mode
                            `((,keyword-regexp 1 ',face-name)))))

(defun asy-add-variable-keywords (function-keywords face-name)
  (let* ((keyword-list (mapcar #'(lambda (x)
                                   (symbol-name  x))
                               function-keywords))
         (keyword-regexp (concat "\\<[0-9]*\\("
                                 (regexp-opt keyword-list)
                                 "\\)\\(?:[^(a-zA-Z]\\|\\'\\)")))
    (font-lock-add-keywords 'asy-mode
                            `((,keyword-regexp 1 ',face-name)))))

;; External definitions of keywords:
;; asy-function-name and asy-variable-name
(load-library "asy-keywords.el")

(defcustom asy-extra-function-name
  '()
  "Extra user function names highlighted with 'font-lock-function-name-face"
  :type '(repeat symbol)
  :group 'asymptote)

(defcustom asy-extra-variable-name '()
  "Extra user variable names highlighted with 'font-lock-constant-face"
  :type '(repeat symbol)
  :group 'asymptote)

(asy-add-variable-keywords
 asy-keyword-name 
 'font-lock-builtin-face)

(asy-add-function-keywords
 (nconc asy-function-name asy-extra-function-name)
 'font-lock-function-name-face)

(asy-add-variable-keywords
 (nconc asy-variable-name asy-extra-variable-name)
 'font-lock-constant-face)

(defface asy-environment-face
  `((t
     (:strike-through ,(face-attribute 'default :foreground) :foreground ,(face-attribute 'default :background))))
  "Face used to highlighting the keywords '\\begin{asy}' and '\\end{asy}' within lasy-mode."
  :group 'asymptote)

(font-lock-add-keywords
 'asy-mode
 '(("\\\\begin{asy}" . 'asy-environment-face)
   ("\\\\end{asy}" . 'asy-environment-face)))

(c-lang-defconst c-block-decls-with-vars
  "Keywords introducing declarations that can contain a block which
might be followed by variable declarations, e.g. like \"foo\" in
\"class Foo { ... } foo;\".  So if there is a block in a declaration
like that, it ends with the following ';' and not right away.

The keywords on list are assumed to also be present on one of the
`*-decl-kwds' lists."
  t        nil
  objc '("union" "enum" "typedef") ;; Asymptote doesn't require ';' after struct
  c '("struct" "union" "enum" "typedef")
  c++      '("class" "struct" "union" "enum" "typedef"))

(setq mode-name "Asymptote")
(if (featurep 'xemacs)
    (turn-on-font-lock)
  (global-font-lock-mode t))
(column-number-mode t)


(defvar asy-menu
  '("Asy"
    ["Toggle lasy-mode"  lasy-mode :visible (and (featurep 'two-mode-mode) two-mode-bool)]
    ["Compile/View"  asy-compile-view t]
    ["Go to error" asy-goto-error t]
    ["Describe command" asy-show-function-at-point t]"--"
    ("Master TeX file"
     ["Set/Change value" (asy-set-master-tex) :active (not (and (boundp two-mode-bool) two-mode-bool)) :key-sequence nil]
     ["Erase value" (asy-unset-master-tex) :active (not (and (boundp two-mode-bool) two-mode-bool)) :key-sequence nil]
     ("Compile OR View"
      ["PS"  asy-master-tex-view-ps :active t]
      ["PDF (pdflatex)" asy-master-tex-view-pdflatex :active t]
      ["PDF (ps2pdf)" asy-master-tex-view-ps2pdf :active t])
     ("Compile AND View"
      ["PS"  asy-master-tex-view-ps-f :active t]
      ["PDF (pdflatex)" asy-master-tex-view-pdflatex-f :active t]
      ["PDF (ps2pdf)" asy-master-tex-view-ps2pdf-f :active t]))
    ["Asymptote insinuates globally LaTeX"  asy-insinuate-latex-globally :active (not asy-insinuate-latex-globally-p)]"--"
    ["Customize" (customize-group "asymptote") :active t :key-sequence nil]
    ["Help" (describe-function 'asy-mode) :active t :key-sequence nil]
    ))
(easy-menu-define asy-mode-menu asy-mode-map "Asymptote Mode Commands" asy-menu)

(defun asy-get-temp-file-name()
  "Get a temp file name for printing."
  (make-temp-file
   (expand-file-name "asy" asy-temp-dir) nil ".asy"))

(defun asy-log-filename()
  (concat "." (file-name-sans-extension (file-name-nondirectory buffer-file-name)) ".log"))

(defun asy-self-compile-view(Filename)
  "Compile Asymptote code Filename and view compilation result with the function 'shell-command'."
  (interactive)
  (let*
       ((asy-command
	(concat asy-command-location
		"asy -V " Filename
                " 2> " (asy-log-filename))))
    (shell-command asy-command)
    (asy-error-message t)
    ))

(defun asy-compile-view()
  "Compile Asymptote code and view compilation result."
  (interactive)
  (if (and (boundp two-mode-bool) two-mode-bool)
      (lasy-compile-view)
    (progn
      (let*
          ((buffer-base-name (file-name-sans-extension (file-name-nondirectory buffer-file-name)))
           (asy-command (concat asy-command-location
                                "asy -V "
                                buffer-base-name
                                ".asy 2> "
				(asy-log-filename))))
        (if (buffer-modified-p) (save-buffer))
        (shell-command asy-command)
        (asy-error-message t)
        ))))

(defun asy-error-message(&optional P)
  (let ((asy-last-error
         (asy-log-field-string
          (asy-log-filename) 0)))
    (if (and asy-last-error (not (string= asy-last-error "")))
        (message (concat asy-last-error (if P "\nPress F4 to goto to error" "")))
      )
    ))

(defun asy-log-field-string(Filename Field)
  "Return field of last line of file filename.
Fields are defined as 'field1:field2.field3:field4' . Field=0 <-> all fields"
  (with-temp-buffer
    (progn
      (insert-file Filename)
      (beginning-of-buffer)
      (if (re-search-forward "^\\(.*?\\): \\(.*?\\)\\.\\(.*?\\):\\(.*\\)$" (point-max) t)
          (progn
            (beginning-of-buffer)
            (while (re-search-forward "^\\(.*?\\): \\(.*?\\)\\.\\(.*?\\):\\(.*\\)$" (point-max) t))
            (match-string Field))
        nil))))

(defun asy-goto-error()
  "Go to point of last error within asy/lasy-mode."
  (interactive)
  (let* ((log-file (asy-log-filename))
         (line_ (asy-log-field-string log-file 2)))
    (if line_
        (if (and (boundp two-mode-bool) two-mode-bool)
            (progn
              (re-search-backward "\\\\begin{asy")
              (next-line (1- (string-to-number line_)))
              (asy-error-message))
          (progn
            (goto-line (string-to-number line_))
            (asy-error-message)))
      (progn (message "No error"))
      )))


(defun asy-grep (Regexp)
  "Internal function used by asymptote."
  (let ((Strout ""))
    (progn
      (beginning-of-buffer)
      (while (re-search-forward Regexp (point-max) t)
        (setq Strout (concat Strout (match-string 0) "\n\n")))
      (if (string= Strout "") "No match.\n" Strout))))


(defun asy-show-function-at-point()
  "Show the Asymptote definitions of the command at point."
  (interactive)
  (save-excursion
    (let ((cWord (current-word))
          (cWindow (selected-window)))
      (switch-to-buffer-other-window "*asy-help*")
      (call-process-shell-command
       (concat asy-command-location "asy -l") nil t nil)
      (let ((rHelp (asy-grep (concat "^.*\\b" cWord "(\\(.\\)*?$"))))
        (erase-buffer)
        (insert rHelp))
      (asy-mode)
      (use-local-map nil)
      (goto-char (point-min))
      (select-window cWindow))))



;;;;;;; TEMPO ;;;;;;;;;;;;;;;
(defvar asy-tempo-tags nil
  "Tempo tags for ASY mode")

;;; ASY-Mode Templates
(require 'tempo)
(require 'advice)
(setq-default tempo-interactive t)
(setq-default
 tempo-match-finder "\\b\\([^\b]+\\)\\=");; The definition in tempo.el is wrong.
(tempo-use-tag-list 'asy-tempo-tags)

;;; Function to construct asy commands
(defun asy-tempo (l)
  "Construct tempo-template for Asymptote commands."
  (let* ((tag (car l))
	 (element (nth 1 l)))
    (tempo-define-template tag element tag nil 'asy-tempo-tags)))

;;; Templates appended to asy-tempo-tags
(mapcar
 'asy-tempo
 '(("dir"  ("{dir(" p ")}"))
   ("intp"  ("intersectionpoint(" p ", " p ")"))
   ("intt"  ("intersectiontime(" p ", " p ")"))
   ("rot"  ("rotate(" p ")*"))
   ("shi"  ("shift(" p ")*"))
   ("sca"  ("scale(" p ")*"))
   ("xsc"  ("xscale(" p ")*"))
   ("ysc"  ("yscale(" p ")*"))
   ("zsc"  ("zscale(" p ")*"))
   ("if"  (& >"if (" p ")"n>
             "{"n>
             r n >
             "}"> %))
   ("els"  (& >"else" n>
              "{"n>
              r n >
              "}"> %))
   ("ife"  (& >"if (" p ")" n>
              "{" n>
              r n
              "}" > n>
              "else" n>
              "{" n>
              p n>
              "}" > %))
   ("for"  (& >"for (" p " ," p " ," p ")" n>
              "{" n>
              r n >
              "}"> %))
   ("whi"  (& >"while (" p ")" n>
              "{" n>
              r n>
              "}"> %))
   
   ))

(add-hook 'asy-mode-hook
	  '(lambda ()
	     (set-variable 'shell-file-name "/bin/sh" t)
	     (tempo-use-tag-list 'asy-tempo-tags)
             (if (boundp flyspell-mode) (flyspell-mode -1))
	     ))

;; Definition of insertion functions
(defun dir()
  (interactive)
  (insert "{dir()}")
  (forward-char -2))

;;; ************************************
;;; asy-mode mixed with LaTeX-mode: lasy
;;; ************************************
(if (require 'two-mode-mode nil t)
    (progn
;;;###autoload
      (defun lasy-mode ()
        "Treat, in some cases, the current buffer as a literal Asymptote program."
        (interactive)
        (set (make-local-variable 'asy-insinuate-latex-p) asy-insinuate-latex-p)
        (setq default-mode    '("LaTeX" latex-mode)
              second-modes     '(("Asymptote"
                                  "\\begin{asy"
                                  "\\end{asy"
                                  asy-mode)))
        (if two-mode-bool
            (progn
              (latex-mode)
              (asy-insinuate-latex)
              )
          (progn
            (two-mode-mode)))
        )
      
      (add-hook 'two-mode-switch-hook
                (lambda ()
                  (if (string= (downcase (substring mode-name 0 5)) "latex")
                      (asy-insinuate-latex))))
      
      
      ;; Solve a problem restoring a TeX file via desktop.el previously in lasy-mode.
      (if (boundp 'desktop-buffer-mode-handlers)
          (progn
            (defun asy-restore-desktop-buffer (desktop-b-f-name d-b-n d-b-m)
              (find-file desktop-b-f-name))
            (add-to-list 'desktop-buffer-mode-handlers
                         '(asy-mode . asy-restore-desktop-buffer))))
      )
  (progn
    (defvar two-mode-bool nil)))

(defvar asy-latex-menu-item
  '("Asymptote" :visible asy-insinuate-latex-p
    ["Toggle lasy-mode"  lasy-mode :active (featurep 'two-mode-mode)]
    ["View asy picture near cursor"  lasy-compile-view :active t]"--"
    ("Compile OR View"
     ["PS"  lasy-view-ps :active t]
     ["PDF (pdflatex)" lasy-view-pdf-via-pdflatex :active t]
     ["PDF (ps2pdf)" lasy-view-pdf-via-ps2pdf :active t])
    ("Compile AND View"
     ["PS"  asy-master-tex-view-ps-f :active t]
     ["PDF (pdflatex)" asy-master-tex-view-pdflatex-f :active t]
     ["PDF (ps2pdf)" asy-master-tex-view-ps2pdf-f :active t])"--"
    ["Asymptote insinuates globally LaTeX"  asy-insinuate-latex-globally :active (not asy-insinuate-latex-globally-p)]
    ("Disable Asymptote insinuate Latex"
     ["locally"  asy-no-insinuate-locally :active t]
     ["globally"  asy-no-insinuate-globally :active t])))


(eval-after-load "latex"
  '(progn
     (if (locate-library "texmathp")
         (prog1
             ;; Not necessary but it's very useful.
             (require 'texmathp)
           (define-key LaTeX-mode-map [(^)] #'(lambda ()
                                                (interactive)
                                                (if (texmathp)
                                                    (progn
                                                      (insert "^{}")
                                                      (backward-char))
                                                  (insert "^"))))
           
           (define-key LaTeX-mode-map [(_)] #'(lambda ()
                                                (interactive)
                                                (if (texmathp)
                                                    (progn
                                                      (insert "_{}")
                                                      (backward-char))
                                                  (insert "_"))))
           )
       (progn
         (message "texmathp not find...")))
     
     (setq lasy-mode-map (copy-keymap LaTeX-mode-map))
     (setq LaTeX-mode-map-backup (copy-keymap LaTeX-mode-map))
     
     (define-key lasy-mode-map (kbd "<C-return>") 'lasy-view-ps)
     (define-key lasy-mode-map (kbd "<C-S-return>") 'asy-master-tex-view-ps-f)
     (define-key lasy-mode-map (kbd "<M-return>") 'lasy-view-pdf-via-pdflatex)
     (define-key lasy-mode-map (kbd "<M-S-return>") 'asy-master-tex-view-pdflatex-f)
     (define-key lasy-mode-map (kbd "<C-M-return>") 'lasy-view-pdf-via-ps2pdf)
     (define-key lasy-mode-map (kbd "<C-M-S-return>") 'asy-master-tex-view-ps2pdf-f)
     (when lasy-keep-key
       (setq LaTeX-mode-map (copy-keymap lasy-mode-map))

       ;; Hack not totally safe.
       ;; Problems may occur if you customize the variables TeX-expand-list or TeX-command-list.
       ;; If you will never customize these variables, you can uncomment the following lines.
;;        (add-to-list 'TeX-expand-list
;;                     '("%a"
;;                       (lambda nil
;;                         asy-command-location)) t)
        
;;        (add-to-list 'TeX-command-list
;;                     '("asy-LaTeX" "%l \"%(mode)\\input{%t}\" && %aasy %s.asy && %l \"%(mode)\\input{%t}\" && %V"
;;                       TeX-run-interactive nil (latex-mode)
;;                       :help "Run LaTeX && Asymptote && LaTeX
;;         Be sure to have
;;         \\usepackage{graphicx}
;;         \\usepackage{asymptote}"))
        
;;        (add-to-list 'TeX-command-list
;;                     '("asy-pdflaTex" "pdflatex -shell-escape %t && %aasy %s.asy && pdflatex -shell-escape %t"
;;                       TeX-run-command nil (latex-mode)
;;                       :help "Run pdflatex && Asymptote && pdflatex
;;         Be sure to have
;;         \\usepackage{graphicx}
;;         \\usepackage{epstopdf}
;;         \\usepackage{asymptote}"))
        
;;        (add-to-list 'TeX-command-list
;;                     '("asy-ps" "%l \"%(mode)\\input{%t}\" && %aasy %s.asy && %(o?)dvips %d -o %f"
;;                       TeX-run-command nil (latex-mode)
;;                       :help "Run LaTeX && Asymptote && LaTeX
;;         Be sure to have
;;         \\usepackage{graphicx}
;;         \\usepackage{asymptote}"))
        
;;        (add-to-list 'TeX-command-list
;;                     '("asy-dvips-pdf" "%l \"%(mode)\\input{%t}\" && %aasy %s.asy && %(o?)dvips %d -o %f && ps2df14 -dPDFSETTINGS=/prepress -dAutoFilterGrayImages=false -dAutoFilterColorImages=false -dColorImageFilter=/FlateEncode -dGrayImageFilter=/FlateEncode -dAutoRotatePages=/None %f %s.pdf"
;;                       TeX-run-command nil (latex-mode)
;;                       :help "Run LaTeX && Asymptote && LaTeX && dvips && ps2pdf14
;;         Be sure to have
;;         \\usepackage{graphicx}
;;         \\usepackage{asymptote}"))

       )
     (easy-menu-define asy-latex-mode-menu lasy-mode-map "Asymptote insinuates LaTeX" asy-latex-menu-item)
     ))

(defvar asy-insinuate-latex-p nil
  "Not nil when current buffer is insinuated by Asymptote.
May be a local variable.
For internal use.")

(defvar asy-insinuate-latex-globally-p nil
  "Not nil when all latex-mode buffers is insinuated by Asymptote.
For internal use.")


(defun asy-no-insinuate-locally ()
  (interactive)
  (set (make-local-variable 'asy-insinuate-latex-p) nil)
  (setq asy-insinuate-latex-globally-p nil)
  (menu-bar-update-buffers)
  (facemenu-update)
  (if (and (boundp 'two-mode-bool) two-mode-bool)
      (lasy-mode))
  (if (not lasy-keep-key) (use-local-map LaTeX-mode-map-backup)))


(defun asy-no-insinuate-globally ()
  (interactive)
  (easy-menu-remove-item LaTeX-mode-map nil "Asymptote")
  (kill-local-variable asy-insinuate-latex-p)
  (setq-default asy-insinuate-latex-p nil)
  (setq asy-insinuate-latex-globally-p nil)
  (menu-bar-update-buffers)
  (facemenu-update)
  (if (not lasy-keep-key) (setq LaTeX-mode-map (copy-keymap LaTeX-mode-map-backup)))
  ;;Disable lasy-mode in all latex-mode buffers.
  (when (featurep 'two-mode-mode)
    (mapc (lambda (buffer)
            (with-current-buffer buffer
              (when (and (buffer-file-name) (string= (file-name-extension (buffer-file-name)) "tex"))
                (latex-mode)
                (setq asy-insinuate-latex-p nil))))
          (buffer-list))))

;;;###autoload
(defun asy-insinuate-latex (&optional global)
  "Add a menu bar in current 'latex-mode' buffer and activate asy keys bindings.
If the optional parameter (only for internal use) 'global' is 't' then all the FUTURE 'latex-mode' buffers are insinuated.
To insinuate all (current and future) 'latex-mode' buffers, use 'asy-insinuate-latex-globally' instead.
You can automate this feature for all the 'latex-mode' buffers by inserting the five following lines in your .emacs initialization file:
   (eval-after-load \"latex\"
     '(progn
        ;; Add here your personal features for 'latex-mode':
        (asy-insinuate-latex t) ;; Asymptote insinuates globally Latex.
        ))"
  (interactive)
  (if (and (not asy-insinuate-latex-globally-p) (or global (string= major-mode "latex-mode")))
      (progn
        (if global
            (progn
              (setq asy-insinuate-latex-p t)
              (setq asy-insinuate-latex-globally-p t)
              (setq LaTeX-mode-map (copy-keymap lasy-mode-map)))
          (progn
            (use-local-map lasy-mode-map)
            (set (make-local-variable 'asy-insinuate-latex-p) t)))        
        )))

(defun asy-insinuate-latex-globally ()
  "Insinuates all (current and future) 'latex-mode' buffers.
See 'asy-insinuate-latex'."
  (interactive)
  (asy-insinuate-latex t)
  (mapc (lambda (buffer)
          (with-current-buffer buffer
            (when (and
                   (buffer-file-name)
                   (string= (file-name-extension (buffer-file-name)) "tex"))
              (setq asy-insinuate-latex-p t)
              (use-local-map LaTeX-mode-map)
              (use-local-map lasy-mode-map))))
        (buffer-list)))

(defun lasy-compile-view()
  "Compile region between \\begin{asy} and \\end{asy}"
  (interactive)
  (save-excursion
    (let ((Filename (asy-get-temp-file-name)))
      (re-search-forward "\\\\end{asy}")
      (re-search-backward "\\\\begin{asy}\\(\n\\|.\\)*?\\\\end{asy}")
      (write-region (match-string 0) 0 Filename)
      (with-temp-file Filename
        (insert-file Filename)
        (beginning-of-buffer)
        (while (re-search-forward "\\\\begin{asy}\\|\\\\end{asy}" (point-max) t)
          (replace-match "")))
      (asy-self-compile-view Filename)
      )))

(defun asy-set-master-tex ()
  "Set the local variable 'asy-TeX-master-file.
This variable is used by 'asy-master-tex-view-ps"
  (interactive)
  (set (make-local-variable 'asy-TeX-master-file)
       (file-name-sans-extension
        (file-relative-name
         (expand-file-name
          (read-file-name "TeX document: ")))))
  (if (string= (concat default-directory asy-TeX-master-file)
               (file-name-sans-extension buffer-file-name))
      (prog1
          (set (make-local-variable 'asy-TeX-master-file) nil)
        (error "You should never give the same name to the TeX file and the Asymptote file"))
    (save-excursion
      (end-of-buffer)
      (if (re-search-backward "asy-TeX-master-file\\(.\\)*$" 0 t)
          (replace-match (concat "asy-TeX-master-file: \"" asy-TeX-master-file "\""))
        (insert (concat "
/// Local Variables:
/// asy-TeX-master-file: \"" asy-TeX-master-file "\"
/// End:")) t))))

(defun asy-unset-master-tex ()
  "Set the local variable 'asy-TeX-master-file to 'nil.
This variable is used by 'asy-master-tex-view-ps"
  (interactive)
  (set (make-local-variable 'asy-TeX-master-file) nil)
  (save-excursion
    (end-of-buffer)
    (if (re-search-backward "^.*asy-TeX-master-file:.*\n" 0 t)
        (replace-match ""))))

(defun asy-master-tex-error ()
  "Asy-mode internal use..."
  (if (y-or-n-p "You try to compile the TeX document that contains this picture.
You must set the local variable asy-TeX-master-file.
Do you want set this variable now ?")
      (asy-set-master-tex) nil))

(defun asy-master-tex-view (Func-view &optional Force)
  "Compile the LaTeX document that contains the picture of the current Asymptote code with the function Func-view.
Func-view can be one of 'lasy-view-ps, 'lasy-view-pdf-via-pdflatex, 'lasy-view-pdf-via-ps2pdf."
  (interactive)
  (if (or
       (and (boundp two-mode-bool) two-mode-bool)
       (string= (downcase (substring mode-name 0 5)) "latex"))
      (progn  ;; Current mode is lasy-mode or latex-mode not asy-mode
        (funcall Func-view Force))
    (if asy-TeX-master-file
        (if (string= asy-TeX-master-file
                     (file-name-sans-extension buffer-file-name))
            (error "You should never give the same name to the TeX file and the Asymptote file")
          (funcall Func-view  Force asy-TeX-master-file))
      (if (asy-master-tex-error)
          (funcall Func-view Force asy-TeX-master-file)))))

(defun lasy-view-ps (&optional Force  Filename )
  "Compile a LaTeX document embedding Asymptote code with latex->asy->latex->dvips and/or view the Poscript output.
If optional argument Force is t then force compilation."
  (interactive)
  (if (buffer-modified-p) (save-buffer))
  (let
      ((b-b-n  (if Filename Filename (file-name-sans-extension buffer-file-name))))
    (if (or (file-newer-than-file-p
             (concat b-b-n ".tex")
             (concat b-b-n ".ps"))
            Force)
        (let
            ((asy-command 
              (concat  "latex  -interaction=nonstopmode " b-b-n ".tex >/dev/null && "
                       "{ if [[ -f " b-b-n ".asy ]]; then " asy-command-location "asy " b-b-n ".asy && latex  -interaction=nonstopmode " b-b-n ".tex >/dev/null ; else true; fi;} && "
                       "dvips -q " b-b-n ".dvi -o " b-b-n ".ps >/dev/null && " ps-view-command " " b-b-n ".ps")))
          (shell-command asy-command)
          ;;(set-window-text-height nil (ceiling (* (frame-height) .7)))
          )
      (let
          ((asy-command 
            (format  "%s %s.ps" ps-view-command b-b-n)))
        (shell-command asy-command))
      )))



(defun lasy-view-pdf-via-pdflatex (&optional Force Filename)
  "Compile a LaTeX document embedding Asymptote code with pdflatex->asy->pdflatex and/or view the PDF output.
If optional argument Force is t then force compilation.
Be sure to have
   \\usepackage{graphicx}
   \\usepackage{epstopdf}
   \\usepackage{asymptote}
in the preamble."
  (interactive)
  (if (buffer-modified-p) (save-buffer))
  (let
      ((b-b-n  (if Filename Filename (file-name-sans-extension buffer-file-name))))
    (if (or (file-newer-than-file-p
             (concat b-b-n ".tex")
             (concat b-b-n ".pdf"))
            Force)
        (let
            ((asy-command 
              (concat  "pdflatex -shell-escape -interaction=nonstopmode " b-b-n ".tex >/dev/null && "
                       "{ if [[ -f " b-b-n ".asy ]]; then " asy-command-location "asy " b-b-n ".asy && pdflatex -shell-escape  -interaction=nonstopmode " b-b-n ".tex >/dev/null ; else true; fi;} && "
                       pdf-view-command " " b-b-n ".pdf &")))
          (shell-command asy-command)
          (set-window-text-height nil (ceiling (* (frame-height) 1)))
          )
      (let
          ((asy-command 
            (format  "%s %s.pdf" pdf-view-command b-b-n)))
        (shell-command asy-command))
      )))




(defun lasy-view-pdf-via-ps2pdf (&optional Force Filename)
  "Compile a LaTeX document embedding Asymptote code with latex->asy->latex->dvips->ps2pdf14 and/or view the PDF output.
If optional argument Force is t then force compilation."
  (interactive)
  (if (buffer-modified-p) (save-buffer))
  (let
      ((b-b-n  (if Filename Filename (file-name-sans-extension buffer-file-name))))
    (if (or (file-newer-than-file-p
             (concat b-b-n ".tex")
             (concat b-b-n ".pdf"))
            Force)
        (let
            ((asy-command 
              (concat  "latex  -interaction=nonstopmode " b-b-n" .tex >/dev/null && "
                       "{ if [[ -f " b-b-n ".asy ]]; then " asy-command-location "asy " b-b-n ".asy && latex  -interaction=nonstopmode " b-b-n ".tex >/dev/null ; else true; fi;} && "
                       "dvips -q -Ppdf -ta4 " b-b-n ".dvi -o " b-b-n ".ps >/dev/null && "
                       "ps2pdf14 -dPDFSETTINGS=/prepress -dAutoFilterGrayImages=false -dAutoFilterColorImages=false -dColorImageFilter=/FlateEncode -dGrayImageFilter=/FlateEncode -dAutoRotatePages=/None " b-b-n ".ps " b-b-n ".pdf >/dev/null && "
                       pdf-view-command " " b-b-n ".pdf")))
          (shell-command asy-command)
          ;;(set-window-text-height nil (ceiling (* (frame-height) .7)))
          )
      (let
          ((asy-command 
            (format  "%s %s.pdf" pdf-view-command b-b-n)))
        (shell-command asy-command))
      )))

;; Goto to the forward/backward tempo's mark
(define-key asy-mode-map [M-right] 'tempo-forward-mark)
(define-key asy-mode-map [M-left]  'tempo-backward-mark)
;; Complete the tempo tag (the first three letters of a keyword)
(define-key asy-mode-map [f3] 'tempo-complete-tag)

;; Goto error of last compilation
(define-key asy-mode-map  (kbd "<f4>") 'asy-goto-error)

;; Save and compile the file with option -V
(define-key asy-mode-map  (kbd "C-c C-c") 'asy-compile-view)

;; Show the definitions of command at point
(define-key asy-mode-map  (kbd "C-c ?") 'asy-show-function-at-point)


(defun asy-master-tex-view-ps ()
  "Look at 'asy-master-tex-view"
  (interactive)
  (asy-master-tex-view 'lasy-view-ps))
(define-key asy-mode-map (kbd "<C-return>") 'asy-master-tex-view-ps)

(defun asy-master-tex-view-ps-f ()
  "Look at 'asy-master-tex-view"
  (interactive)
  (asy-master-tex-view 'lasy-view-ps t))
(define-key asy-mode-map (kbd "<C-S-return>") 'asy-master-tex-view-ps-f)

(defun asy-master-tex-view-pdflatex ()
  "Look at 'asy-master-tex-view"
  (interactive)
  (asy-master-tex-view 'lasy-view-pdf-via-pdflatex))
(define-key asy-mode-map (kbd "<M-return>") 'asy-master-tex-view-pdflatex)

(defun asy-master-tex-view-pdflatex-f ()
  "Look at 'asy-master-tex-view"
  (interactive)
  (asy-master-tex-view 'lasy-view-pdf-via-pdflatex t))
(define-key asy-mode-map (kbd "<M-S-return>") 'asy-master-tex-view-pdflatex-f)

(defun asy-master-tex-view-ps2pdf ()
  "Look at 'asy-master-tex-view"
  (interactive)
  (asy-master-tex-view 'lasy-view-pdf-via-ps2pdf))
(define-key asy-mode-map (kbd "<C-M-return>") 'asy-master-tex-view-ps2pdf)

(defun asy-master-tex-view-ps2pdf-f ()
  "Look at 'asy-master-tex-view"
  (interactive)
  (asy-master-tex-view 'lasy-view-pdf-via-ps2pdf t))
(define-key asy-mode-map (kbd "<C-M-S-return>") 'asy-master-tex-view-ps2pdf-f)

(provide `asy-mode)
