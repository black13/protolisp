char firmware [] =
"(define list (lambda n n))\n"
"\n"
"(define (sublis l exp)\n"
  "(if (cons? exp)\n"
      "(cons (sublis l (car exp))\n"
         "(sublis l (cdr exp)))\n"
      "(let ((cell (assq exp l)))\n"
        "(if cell (cdr cell) exp))))\n"
"\n"
"(define (cadr x) (car (cdr x)))\n"
"(define (caddr x) (car (cdr (cdr x))))\n"
"(define (cdddr x) (cdr (cdr (cdr x))))\n"
"\n"
"(define (replace before after)\n"
  "(set-car! before (car after))\n"
"  (set-cdr! before (cdr after))\n"
  "after)\n"
"\n"
"(define (push-macro form)\n"
  "(replace form\n"
         "(list 'set! (caddr form)\n"
                 "(list 'cons (cadr form) (caddr form)))))\n"
"\n"
"(define (pop-macro form)\n"
  "(replace form\n"
         "(list 'let (list (list 'tmp (cadr form)))\n"
                 "(list 'set! (cadr form) '(cdr tmp))\n"
"                 '(car tmp))))\n"
"\n"
"(define push 'push-macro)\n"
"(define pop 'pop-macro)\n"
"\n"
"(define (defvar-macro form)\n"
  "(list 'or\n"
        "(list 'value-cell (list 'quote (cadr form)))\n"
"        (list 'define (cadr form) (caddr form))))\n"
"\n"
"(define defvar 'defvar-macro)\n"
"\n"
"(define (defun-macro form)\n"
  "(cons 'define\n"
        "(cons (cons (cadr form) (caddr form))\n"
         "(cdddr form))))\n"
"\n"
"(define defun 'defun-macro)\n"
        "\n"
"(define setq set!)\n"
"(define progn begin)\n"
"\n"
"(define the-empty-stream ())\n"
"\n"
"(define empty-stream? null?)\n"
"\n"
"(define (*cons-stream head tail-future)\n"
  "(list head () () tail-future))\n"
"\n"
"(define head car)\n"
"\n"
"(define (tail x)\n"
  "(if (car (cdr x))\n"
      "(car (cdr (cdr x)))\n"
"      (let ((value ((car (cdr (cdr (cdr x)))))))\n"
        "(set-car! (cdr x) t)\n"
"        (set-car! (cdr (cdr x)) value))))\n"
"\n"
"(define (cons-stream-macro form)\n"
  "(replace form\n"
         "(list '*cons-stream\n"
                 "(cadr form)\n"
"                 (list 'lambda () (caddr form)))))\n"
"\n"
"(define cons-stream 'cons-stream-macro)\n"
"\n"
"(define (enumerate-interval low high)\n"
  "(if (> low high)\n"
      "the-empty-stream\n"
"      (cons-stream low (enumerate-interval (+ low 1) high))))\n"
"\n"
"(define (print-stream-elements x)\n"
  "(if (empty-stream? x)\n"
      "()\n"
"      (begin (print (head x))\n"
         "(print-stream-elements (tail x)))))\n"
"\n"
"(define (standard-fib x)\n"
  "(if (< x 2)\n"
      "x\n"
"      (+ (standard-fib (- x 1))\n"
         "(standard-fib (- x 2)))))\n";