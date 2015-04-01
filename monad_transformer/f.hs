import Control.Monad
import Control.Applicative
data MaybeT m a = MaybeT {
        runMaybeT :: m (Maybe a)
}
type MIO  = MaybeT IO 
class MonadTrans t where 
    lift ::(Monad m) => m a -> t m a
instance (Functor m) => Functor (MaybeT m) where 
    fmap  = undefined
instance (Applicative m) => Applicative (MaybeT m) where 
    pure  = undefined
    (<*>) = undefined
instance Monad m => Monad (MaybeT m) where 
    return x = MaybeT $ return $ Just x
    x >>= f = MaybeT $ do may <- runMaybeT x
                          case may of 
                            Nothing -> return Nothing
                            Just a  -> runMaybeT (f a)
instance MonadTrans MaybeT where 
    lift x = MaybeT $ do val <- x
                         return $ Just val
getValidPassphrase :: MaybeT IO String
getValidPassphrase = do s <- lift getLine
                        return s
askPassphrase :: MaybeT IO ()
askPassphrase = do lift $ putStrLn "Insert your new passphrase:"
                   value <- getValidPassphrase
                   lift $ putStrLn $ show value

main = runMaybeT askPassphrase
