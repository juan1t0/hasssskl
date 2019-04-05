import Text.Printf
import Control.Exception
import System.CPUTime

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

ternary  list val low hi | list == [] = (-1)
                         | hi < low = (-1)
                         | list !! (fst medio) == val = (fst medio)
                         | list !! (snd medio) == val = (snd medio)
                         | list !! (fst medio) > val = ternary list val (low) ((fst medio) -1)
                         | list !! (fst medio) < val && list !! (snd medio) > val = ternary list val ((fst medio)+1) ((snd medio)-1)
                         | list !! (snd medio) < val = ternary list val ((snd medio)+1) (hi-1)
                         where medio = (low+(div (hi-low) 3), (hi-(div (hi-low) 3)))


time :: IO t -> IO t
time a = do
    start <- getCPUTime
    v <- a
    x = ternary [1..10] 1 0 10
    end   <- getCPUTime
    let diff = (fromIntegral (end - start)) / (10^12)
    printf "Computation time: %0.3f sec\n" (diff :: Double)
    return v

--main = do
--    putStrLn "Starting..."
  --  time $ product [1..10000] `seq` return ()
    --putStrLn "Done."
