#lang racket
;; Actividad Integradora 3.4 Resaltador de sintaxis

;; Eduardo Rodríguez Gil - A01274913

;; Caso de prueba c++: (input read_file "c++").
;; Caso de prueba python: (input read_file "python").

(require 2htdp/batch-io)

;; Define los caracteres.
(define characters
  '("a" "b" "c" "d" "e" "f" "g" "h" "i" "j" "k" "l" "m" "n" "o" "p" "q" "r" "s" "t" "u" "v" "w" "x" "y" "z"))

;; Define los numeros.
(define numbers
  '("0" "1" "2" "3" "4" "5" "6" "7" "8" "9"))

;; Define operadores.
(define operators
  '("+" "-" "/" "*" "%" "(" ")" "&" "{" "}" ";" ":" "[" "]" "|" "," "="))

;; Define los valores reservados.
(define for_reserved
 '("for" "while" "if" "do" "switch" "else" "case" "return" "true" "false" "using" "namespace"
   "cout" "is" "del" "break" "return" "from" "elif" "and" "as" "range" "class" "not"
   "def" "exec" "while" "or" "except" "print" "import"))

;; Define librerias.
(define for_library
  '("#include" "import" "from"))

;; Define los tipos de dato
(define type_data
  '("int" "char" "string" "float" "long" "double" "bool" "void"))

;; Lee el archivo.
(define read_file
  "C:\\Users\\edy11\\OneDrive\\Documentos\\Actividad Integradora 3.4 Resaltador de sintaxis\\input_cpp.txt")

;; Escribe el archivo obtenido.
(define write_file
  "C:\\Users\\edy11\\OneDrive\\Documentos\\Actividad Integradora 3.4 Resaltador de sintaxis\\index.html")

;; Texto con formato en HTML
(define text
  '("<title>Actividad Integradora 3.4 Resaltador de sintaxis</title>" "\n"
"<link rel='stylesheet' href='styles.css'>" "\n"))

;; Obitiene los caracteres ya definidos.
(define get_characters
  (lambda (char characters)
   (cond[(null? characters) #f]
     [(string-ci=? char (car characters)) #t]
     [else (get_characters char (cdr characters))])))

;; Obtiene los numeros ya definidos.
(define get_numbers
  (lambda (numero numbers)
   (cond
     [(null? numbers) #f]
     [(string-ci=? numero (car numbers)) #t]
     [else (get_numbers numero (cdr numbers))])))

;; Obtiene los operadores ya definidos.
(define get_operators
  (lambda (operator operators)
   (cond
     [(null? operators) #f]
     [(string-ci=? operator (car operators)) #t]
     [else (get_operators operator (cdr operators))])))

;; Obtiene los valores reservados ya definidos
(define get_for_reserved
  (lambda (for for_reserved)
    (cond
     [(null? for_reserved) #f]
     [(string-ci=? for (car for_reserved)) #t]
     [else (get_for_reserved for (cdr for_reserved))])))

;; Obtiene las librerias ya definidas
(define get_for_library
  (lambda (library for_library)
    (cond
     [(null? for_library) #f]
     [(string-ci=? library (car for_library)) #t]
     [else (get_for_library library (cdr for_library))])))

;; Obtiene los tipos de datos ya definidos
(define get_type_data
  (lambda (data type_data)
    (cond
     [(null? type_data) #f]
     [(string-ci=? data (car type_data)) #t]
     [else (get_type_data data (cdr type_data))])))

(define search_word
  (lambda (list text word)
    (cond
      [(null? list) ((copy write_file) text)]
      [(get_for_reserved word for_reserved) (read_text list (cons "</span>" (cons word (cons "<span class='reserved'>" text))))]
      [(get_for_library word for_library) (read_text list (cons "</span>" (cons word (cons "<span class='library'>" text))))]
      [(get_type_data word type_data) (read_text list (cons "</span>" (cons word (cons "<span class='data'>" text))))]
      [(string-ci=? (car list) " ") (read_text list (cons word text))]
      [(string-ci=? (car list) "\n") (read_text list (cons word text))]
      [(get_numbers (car list) numbers) (read_text list (cons word text))]
      [(get_operators (car list) operators) (read_text list (cons word text))]
      [else (search_word (cdr list) text (~a word (car list)))])))

(define read_text
  (lambda (list text)
    (cond
      [(null? list) ((copy write_file) (cons "\n"(cons "</html>" (cons "\n" (cons "</body>" (cons "\n" text))))))]
      [(string-ci=? (car list) " ") (read_text (cdr list) (cons "&nbsp;" text))]
      [(string-ci=? (car list) "\n") (read_text (cdr list) (cons "<p>" (cons "\n" (cons "</p>" text))))]
      [(get_numbers (car list) numbers) (read_text (cdr list) (cons "</span>" (cons (car list) (cons "<span class='numbers'>" text))))]
      [(get_operators (car list) operators) (read_text (cdr list) (cons "</span>" (cons (car list) (cons "<span class='operators'>" text))))]
      [else (search_word (cdr list) text (~a "" (car list)))])))

;; Identifica el archivo
(define identifies_type_file
  (lambda (file type_file)
  (cond
    [(string-ci=? type_file "c++") (read_text list text)]
    [(string-ci=? type_file "python") (read_text list text)]
    [else (copy "No valido")])))

;; Se define la entrada del archivo
(define input
  (lambda (file type_file)
    (identifies_type_file file type_file)))

;; Se define la lista
(define list
  (read-1strings read_file))

;; Escribe en un archivo de texto
(define copy
  (lambda (destiny)
    (lambda (text)
    (write-file destiny (string-join (reverse text) "\n")))))