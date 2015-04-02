import Control.Monad
import Control.Applicative
import Control.Monad.Writer hiding(lift)
import MaybeT


fib :: Integer->Integer
fib n | n < 0  = error "negative number!"
      | n <= 1 = 1
      | otherwise = fib (n-1) + fib (n-2)

fibMaybe :: Integer->Maybe Integer
fibMaybe n  | n < 0     = Nothing
            | n <= 1    = return 1
            | otherwise = do
                f1 <- fibMaybe (n-1)
                f2 <- fibMaybe (n-2)
                return $ f1 + f2

fibWriter :: Integer->Writer [String] Integer
fibWriter n | n < 0  = error  "negative number!"
            | n <= 1 = do
                tell $ ["fib " ++ (show n) ++ " = 1"]
                return 1
            | otherwise = do
                tell $ ["fib " ++ (show n) ++ " = fib " ++ show (n-1) ++ " + fib " ++ show (n-2)]
                f1 <- fibWriter (n-1)
                f2 <- fibWriter (n-2)
                return $ f1 + f2

fibMaybeWriter :: Integer->MaybeT (Writer [String]) Integer
fibMaybeWriter n 
    | n < 0   = MaybeT $ do
        tell ["negative number"] 
        return Nothing
    | n <= 1  = do
        lift $ tell $ ["fib " ++ (show n) ++ " = 1"]
        return 1
    | otherwise = do
        lift $ tell $ ["fib " ++ (show n) ++ " = fib " ++ show (n-1) ++ " + fib " ++ show (n-2)]
        f1 <- fibMaybeWriter (n-1)
        f2 <- fibMaybeWriter (n-2)
        return $ f1 + f2
main :: IO ()
main = do 
    n <- liftM read getLine
    let result = runWriter $ runMaybeT $ fibMaybeWriter n 
        val = fst result
        log = snd result 
     in do
         mapM_ putStrLn log
         putStrLn "---------------"
         putStrLn $ show val


