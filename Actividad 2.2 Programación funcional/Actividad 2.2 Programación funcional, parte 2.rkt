#lang racket
;; Actividad 2.2 Programación funcional, parte 2
;; Eduardo Rodríguez Gil - A01274913
;; Michelle Aylin Calzada Montes - A01706202


;; Ejercicio 1: insert
(define my-append
  
  (lambda (lst1 lst2)
    (cond
      [(null? lst1) lst2]
      [else (cons (car lst1)
                  (my-append (cdr lst1) lst2))])))

(define in-lst
  (lambda (elem)
    (cons elem '())))

(define insert
  (lambda (n lst)
    (cond
      [(null? lst) (my-append lst (in-lst n))]
      [else (insertion-sort (my-append lst (in-lst n)))])))
;; Example 1: (insert 14 '()) => (14)
;; Example 2: (insert 4 '(5 6 7 8)) => (4 5 6 7 8)
;; Example 3: (insert 5 '(1 3 6 7 9 16)) => (1 3 5 6 7 9 16)
;; Example 4: (insert 10 '(1 5 6)) => (1 5 6 10)


;; Ejercicio 2: insertion-sort
(define insertion
  (lambda (n lst)
    (if (null? lst)
        (list n)
        (let ((x (car lst))
              (xs (cdr lst)))
          (if (<= n x)
              (cons n lst)
              (cons x (insertion n xs)))))))

(define insertion-sort
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [else (insertion (car lst)
                     (insertion-sort (cdr lst)))])))
;; Example 1: (insertion-sort '()) => ()
;; Example 2: (insertion-sort '(4 3 6 8 3 0 9 1 7)) => (0 1 3 3 4 6 7 8 9)
;; Example 3: (insertion-sort '(1 2 3 4 5 6)) => (1 2 3 4 5 6)
;; Example 4: (insertion-sort '(5 5 5 1 5 5 5)) => (1 5 5 5 5 5 5)


;; Ejercicio 3: rotate-left
(define reverse
  (lambda (list)
    (cond
      [(null? list) '()]
      [else (my-append (reverse (cdr list))
                       (cons (car list) '()))])))

(define rotate-left
  (lambda (n lst)
    (cond
      [(null? lst) '()]
      [(eq? n 0) lst]
      [(< n 0) (rotate-left (+ n 1) (my-append (in-lst (car (reverse lst))) (reverse (cdr (reverse lst)))))]
      [else (rotate-left (- n 1) (my-append (cdr lst) (in-lst (car lst))))])))
;;Example 1: (rotate-left 5 '()) => ()
;;Example 2: (rotate-left 0 '(a b c d e f g)) => (a b c d e f g)
;;Example 3: (rotate-left 1 '(a b c d e f g)) => (b c d e f g a)
;;Example 4: (rotate-left -1 '(a b c d e f g)) => (g a b c d e f)
;;Example 5: (rotate-left 3 '(a b c d e f g)) => (d e f g a b c)
;;Example 6: (rotate-left -3 '(a b c d e f g)) => (e f g a b c d)
;;Example 7: (rotate-left 8 '(a b c d e f g)) => (b c d e f g a)
;;Example 8: (rotate-left -8 '(a b c d e f g)) => (g a b c d e f)
;;Example 9: (rotate-left 45 '(a b c d e f g)) => (d e f g a b c)
;;Example 10: (rotate-left -45 '(a b c d e f g)) => (e f g a b c d)


;; Ejercicio 4: prime-factors
(define prime-factors
  (lambda (n)
    [let recursive ((n n) (x 2))
      (cond
        [(= n 1) '()]
        [(= 0 (modulo n x)) (cons x (recursive (/ n x) x))]
        [else (recursive n (+ 1 x))])]))
;; Example 1: (prime-factors 1) => ()
;; Example 2: (prime-factors 6) => (2 3)
;; Example 3: (prime-factors 96) => (2 2 2 2 2 3)
;; Example 4: (prime-factors 97) => (97)
;; Example 5: (prime-factors 666) => (2 3 3 37)


;; Ejercicio 5: gcd
(define gcd
  (lambda (a b)
    (cond
      [(= b 0) a]
      [else (gcd b (modulo a b))])))
;; Example 1: (gcd 13 7919) => 1
;; Example 2: (gcd 20 16) => 4
;; Example 3: (gcd 54 24) => 6
;; Example 4: (gcd 6307 1995) => 7
;; Example 5: (gcd 48 180) => 12
;; Example 6: (gcd 42 56) => 14


;; Ejercicio 6: deep-reverse
(define deep-reverse
  (lambda (lst)
    [if (list? lst)
        (reverse (map deep-reverse lst)) lst]))
;; Example 1: (deep-reverse '()) => '()
;; Example 2: (deep-reverse '(a (b c d) 3)) => (3 (d c b) a)
;; Example 3: (deep-reverse '((1 2) 3 (4 (5 6)))) => (((6 5) 4) 3 (2 1))
;; Example 4: (deep-reverse '(a (b (c (d (e (f (g (h i j))))))))) => ((((((((j i h) g) f) e) d) c) b) a)


;; Ejercicio 7: insert-everywhere
(define insert-anywhere
  (lambda (position element lista)
    [if (empty? lista) (list element)
        [if (= 1 position)
            (cons element lista)
            (cons (first lista)
                  [insert-anywhere (- position 1) element (rest lista)])]]))

(define insert-everywhere
  (lambda (x lst)
    (map
     (lambda (n)
       [insert-anywhere n x lst])
     [range 1 (+ 2 (length lst))])))
;; Example 1: (insert-everywhere 1 '()) => ((1))
;; Example 2: (insert-everywhere 1 '(a)) => ((1 a) (a 1))
;; Example 3: (insert-everywhere 1 '(a b c)) => ((1 a b c) (a 1 b c) (a b 1 c) (a b c 1))
;; Example 4: (insert-everywhere 1 '(a b c d e)) => ((1 a b c d e)
;;                                                  (a 1 b c d e)
;;                                                  (a b 1 c d e)
;;                                                  (a b c 1 d e)
;;                                                  (a b c d 1 e)
;;                                                  (a b c d e 1))
;; Example 5: (insert-everywhere 'x '(1 2 3 4 5 6 7 8 9 10)) => ((x 1 2 3 4 5 6 7 8 9 10)
;;                                                              (1 x 2 3 4 5 6 7 8 9 10)
;;                                                              (1 2 x 3 4 5 6 7 8 9 10)
;;                                                              (1 2 3 x 4 5 6 7 8 9 10)
;;                                                              (1 2 3 4 x 5 6 7 8 9 10)
;;                                                              (1 2 3 4 5 x 6 7 8 9 10)
;;                                                              (1 2 3 4 5 6 x 7 8 9 10)
;;                                                              (1 2 3 4 5 6 7 x 8 9 10)
;;                                                              (1 2 3 4 5 6 7 8 x 9 10)
;;                                                              (1 2 3 4 5 6 7 8 9 x 10)
;;                                                              (1 2 3 4 5 6 7 8 9 10 x))


;; Ejercicio 8: pack
(define sub-pack
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [else (my-append (in-lst (repeat-head (cadr (car lst)) (car (car lst)))) (sub-pack (cdr lst)))])))

(define pack
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [else (sub-pack (encode lst))])))
;; Example 1: (pack '()) ⇒ ()
;; Example 2: (pack '(a a a a b c c a a d e e e e) )⇒ ((a a a a) (b) (c c) (a a) (d) (e e e e))
;; Example 3: (pack '(1 2 3 4 5)) ⇒ ((1) (2) (3) (4) (5))
;; Example 4: (pack '(9 9 9 9 9 9 9 9 9)) ⇒ ((9 9 9 9 9 9 9 9 9))


;; Ejercicio 9: compress
(define compress
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [(< (length lst) 2) (my-append (in-lst (car lst)) '())]
      [(eq? (car lst) (cadr lst)) (compress (cdr lst))]
      [else (my-append (in-lst (car lst)) (compress (cdr lst)))])))
;; Example 1: (compress '()) => ()
;; Example 2: (compress '(a b c d)) => (a b c d)
;; Example 3: (compress '(a a a a b c c a a d e e e e)) => (a b c a d e)
;; Example 4: (compress '(a a a a a a a a a a)) => (a)


;; Ejercicio 10: encode
(define count
  (lambda (n e)
    (cond
      [(null? e) '()]
      [(< (length e) 2) (in-lst (my-append (in-lst n) (in-lst (car e))))]
      [(eq? (car e) (cadr e)) (count  (+ n 1) (cdr e))]
      [else (in-lst (my-append (in-lst n) (in-lst (car e))))])))
    
(define code
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [else (my-append (count 1 lst)
                       (code (cdr lst)))])))

(define quitar
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [(< (length lst) 2) (my-append lst '())]
      [(eq? (cadr (car lst)) (cadr (cadr lst))) (quitar (cdr lst))]
      [else  (my-append (in-lst (car lst))
                       (quitar (cdr lst)))])))

(define encode
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [else (reverse (quitar (reverse (code lst))))])))
;; Example 1: (encode '()) => ()
;; Example 2: (encode '(a a a a b c c a a d e e e e)) => ((4 a) (1 b) (2 c) (2 a) (1 d) (4 e))
;; Example 3: (encode '(1 2 3 4 5)) => ((1 1) (1 2) (1 3) (1 4) (1 5))
;; Example 4: (encode '(9 9 9 9 9 9 9 9 9)) => ((9 9))


;; Ejercicio 11: encode-modified
(define modified
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [(< (length lst) 2) (cond
                            [(eq? (car (car lst)) 1) (my-append (in-lst (cadr (car lst))) '())]
                            [else (my-append (in-lst (car lst)) '())])]
      [(eq? (car (car lst)) 1) (my-append (in-lst (cadr (car lst))) (modified (cdr lst)))]
      [else (my-append (in-lst (car lst)) (modified (cdr lst)))])))

(define encode-modified
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [else (modified (encode lst))])))
;; Example 1: (encode-modified '()) => ()
;; Example 2: (encode-modified '(a a a a b c c a a d e e e e)) => ((4 a) b (2 c) (2 a) d (4 e))
;; Example 3: (encode-modified '(1 2 3 4 5)) => (1 2 3 4 5)
;; Example 4: (encode-modified '(9 9 9 9 9 9 9 9 9)) => ((9 9))


;; Ejercicio 12: decode
(define repeat-head
  (lambda (atom amount)
    (cond
      [(eq? amount 0) '()]
      [else (cons atom (repeat-head atom (- amount 1)))])))

(define mult
  (lambda (elem)
    (cond
      [(pair? elem) (repeat-head (cadr elem) (car elem))]
      [else (in-lst elem)])))

(define decode
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [else (my-append (mult (car lst))
                       (decode (cdr lst)))])))
;; Example 1: (decode '()) => ()
;; Example 2: (decode '((4 a) b (2 c) (2 a) d (4 e))) => (a a a a b c c a a d e e e e)
;; Example 3: (decode '(1 2 3 4 5)) => (1 2 3 4 5)
;; Example 4: (decode '((9 9))) => (9 9 9 9 9 9 9 9 9)