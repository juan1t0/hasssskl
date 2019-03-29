imprime x | x == 1 = "1"
          | otherwise = (show x) ++ " "++imprime (x-1)

factorial :: Integer -> Integer
factorial x | x == 0 = 1
            | x == 1 = 1
            | otherwise = x * factorial (x-1)

fibonacci :: Integer -> Integer
fibonacci x | x == 0 = x
            | x == 1 = x
            |otherwise = fibonacci(x-1) + fibonacci(x-2)

recorrer (x:xs)| xs==[] = show (x) 
               |otherwise = show(x) ++","++ recorrer (xs)

fun::[Char] -> [Char]
fun x = y
        where y = (x++x)

binary:: [Int] -> Int ->Int -> Int -> Int
binary  list val izq der | list == [] = (-1)
                         | izq >= der = (-1)
                         | list !! medio == val = medio
                         | list !! medio > val = binary list val izq (medio)
                         | list !! medio < val = binary list val (medio+1) der
                         where medio = (div (izq+der) 2)