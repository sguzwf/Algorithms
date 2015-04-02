module MaybeT where
import Control.Monad
import Control.Applicative 
newtype MaybeT m a= MaybeT {
    runMaybeT :: m (Maybe a)
}
class MonadTrans t where 
    lift :: (Monad m) => m a -> t m a
instance Functor (MaybeT a) where 
    fmap = undefined
instance Applicative (MaybeT a) where 
    pure  = undefined
    (<*>) = undefined
instance (Monad m) => Monad (MaybeT m) where 
    return x = MaybeT $ return $ Just x
    x >>= f  = MaybeT $ do may <- runMaybeT x
                           case may of
                             Nothing  -> return Nothing
                             Just val -> runMaybeT $ f val
instance MonadTrans MaybeT where 
    -- lift :: (Monad m) => m a -> MaybeT m a
    lift mv = MaybeT $ mv >>= return . Just
