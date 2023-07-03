{-# LANGUAGE FlexibleInstances #-}

module PE3 where

import Data.List (sort, sortBy)
import Text.Printf (printf)

data Term = Const Integer | Pw Integer Power | Trig Integer Power Trigonometric | Exp Integer Power Exponential

data Power = Power Integer
data Polynomial = Polynomial [(Integer, Power)]
data Exponential = Exponential Polynomial
data Trigonometric = Sin Polynomial | Cos Polynomial

class Evaluable a where
    function :: a -> (Integer -> Double)

class Differentiable a where
    derivative :: a -> [Term]

-- You can use this as is
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x

-- You don't have to follow the order the functions appear in the file
-- For example, you could first define all Show instances, then all Eq instances etc.
-- if that implementation order is more convenient for you.

-- INSTANCES FOR POWER

instance Show Power where
    show (Power 0) = "1"
    show (Power 1) = "x"
    show (Power n) = "x^" ++ (show n)

instance Eq Power where
    (Power a) == (Power b) = a == b

instance Ord Power where
    (Power a) <= (Power b) = a <= b

instance Evaluable Power where -- (Power 2) 3 = 9
    function (Power n) = \x -> getRounded ((fromIntegral x) ** (fromIntegral n))

instance Differentiable Power where
    derivative (Power 0) = [Const 0]
    derivative (Power 1) = [Const 1]
    derivative (Power n) = [Pw n (Power (n-1))]



-- INSTANCES FOR POLYNOMIAL

instance Show Polynomial where
    show (Polynomial terms) = showPoly terms
        where
            showPoly [] = ""
            showPoly ((0, _):xs) = showPoly xs
            showPoly [(-1, p)] = "-" ++ show p
            showPoly [(1, p)] = show p
            showPoly [(n, Power 0)] = show n
            showPoly [(n, p)] = show n ++ show p
            showPoly ((-1, p):xs) = "-" ++ show p ++ " + " ++ showPoly xs
            showPoly ((1, p):xs) = show p ++ " + " ++ showPoly xs
            showPoly ((n, p):xs) = show n ++ show p ++ " + " ++ showPoly xs

instance Eq Polynomial where
    (Polynomial a) == (Polynomial b) = (sort a) == (sort b)


instance Evaluable Polynomial where
    function (Polynomial terms) = \x -> getRounded (sum (map (\(n, p) -> (fromIntegral n) * (function p x)) terms))

instance Differentiable Polynomial where -- (Pw 2 (Power 3)) = 2 * 3 * x^2
    derivative (Polynomial []) = []
    derivative (Polynomial ((0, _):xs)) = combineTerms (derivative (Polynomial xs))
    derivative (Polynomial ((1, p):xs)) = combineTerms ((derivative p) ++ (derivative (Polynomial xs)))
    derivative (Polynomial ((n, p):xs)) = combineTerms (map (\(Pw m po) -> Pw (n*m) po) ((derivative p)) ++ (derivative (Polynomial xs)))



-- INSTANCES FOR EXPONENTIAL

instance Show Exponential where
    show (Exponential (Polynomial [])) = ""
    show (Exponential (Polynomial [(0, _)])) = "1"
    show (Exponential (Polynomial [(1, Power 0)])) = "e"
    show (Exponential (Polynomial [(-1, Power 0)])) = "e^(-1)"
    show (Exponential (Polynomial [(n, Power 0)])) = "e^" ++ (show n)
    show (Exponential (Polynomial [(1, Power 1)])) = "e^" ++ "x"
    show (Exponential (Polynomial [(-1, Power 1)])) = "e^(-x)"
    show (Exponential (Polynomial [(n, Power 1)])) = if (n > 0) then "e^" ++ (show n) ++ "x" else "e^(" ++ (show n) ++ "x)"
    show (Exponential (poly)) = "e^(" ++ (show poly) ++ ")"

instance Eq Exponential where
    (Exponential a) == (Exponential b) = a == b 

instance Evaluable Exponential where
    function (Exponential poly) = \x -> getRounded (exp (function poly x))

instance Differentiable Exponential where -- e^(x^2 + 3x + 5) = 2xe^(x^2 + 3x + 5) + 3e^(x^2 + 3x + 5)
    derivative (Exponential poly) =
        let polyDerivative = derivative poly
        in map (\term -> case term of
                          (Const c) -> Exp c (Power 0) (Exponential poly)
                          (Pw n p) -> Exp n p (Exponential poly)
                          _ -> Const 0
               ) polyDerivative
    
    
    
-- INSTANCES FOR TRIGONOMETRIC

instance Show Trigonometric where
    show (Sin (Polynomial [])) = "sin0"
    show (Sin (Polynomial [(0, _)])) = "sin0"
    show (Sin (Polynomial [(1, Power 0)])) = "sin1"
    show (Sin (Polynomial [(-1, Power 0)])) = "sin(-1)"
    show (Sin (Polynomial [(n, Power 0)])) = "sin" ++ (show n)
    show (Sin (Polynomial [(1, Power 1)])) = "sinx"
    show (Sin (Polynomial [(-1, Power 1)])) = "sin(-x)"
    show (Sin (Polynomial [(n, Power 1)])) = if (n > 0) then "sin" ++ (show n) ++ "x" else "sin(" ++ (show n) ++ "x)"
    show (Sin (poly)) = "sin(" ++ (show poly) ++ ")"
    show (Cos (Polynomial [])) = "cos0"
    show (Cos (Polynomial [(0, _)])) = "cos0"
    show (Cos (Polynomial [(1, Power 0)])) = "cos1"
    show (Cos (Polynomial [(-1, Power 0)])) = "cos(-1)"
    show (Cos (Polynomial [(n, Power 0)])) = "cos" ++ (show n)
    show (Cos (Polynomial [(1, Power 1)])) = "cosx"
    show (Cos (Polynomial [(-1, Power 1)])) = "cos(-x)"
    show (Cos (Polynomial [(n, Power 1)])) = if (n > 0) then "cos" ++ (show n) ++ "x" else "cos(" ++ (show n) ++ "x)"
    show (Cos (poly)) = "cos(" ++ (show poly) ++ ")"

instance Eq Trigonometric where
    (Sin poly1) == (Sin poly2) = poly1 == poly2
    (Cos poly1) == (Cos poly2) = poly1 == poly2
    _ == _ = False  

instance Evaluable Trigonometric where
    function (Sin poly) = \x -> getRounded (sin (function poly x))
    function (Cos poly) = \x -> getRounded (cos (function poly x))

instance Differentiable Trigonometric where
    derivative (Sin poly) = 
        let polyDerivative = derivative poly
        in map (\term -> case term of
                          (Const c) -> Trig c (Power 0) (Cos poly)
                          (Pw n p) -> Trig n p (Cos poly)
                          _ -> Const 0
               ) polyDerivative
    derivative (Cos poly) = 
        let polyDerivative = derivative poly
        in map (\term -> case term of
                          (Const c) -> Trig (-c) (Power 0) (Sin poly)
                          (Pw n p) -> Trig (-n) p (Sin poly)
                          _ -> Const 0
               ) polyDerivative



-- INSTANCES FOR TERM

instance Show Term where
    show (Const 0) = "0"
    show (Const n) = show n
    show (Pw 0 _) = "0"
    show (Pw (-1) p) = "-" ++ show p
    show (Pw 1 p) = show p
    show (Pw n p) = show n ++ show p
    show (Exp 0 _ _) = "0"
    show (Exp (-1) (Power 0) e) = "-" ++ show e
    show (Exp (-1) p e) = "-" ++ show p ++ show e
    show (Exp 1 (Power 0) e) = show e
    show (Exp 1 p e) = show p ++ show e
    show (Exp n (Power 0) e) = show n ++ show e
    show (Exp n p e) = show n ++ show p ++ show e
    show (Trig 0 _ _) = "0"
    show (Trig (-1) (Power 0) t) = "-" ++ show t
    show (Trig (-1) p t) = "-" ++ show p ++ show t
    show (Trig 1 (Power 0) t) = show t
    show (Trig 1 p t) = show p ++ show t
    show (Trig n (Power 0) t) = show n ++ show t
    show (Trig n p t) = show n ++ show p ++ show t

instance Eq Term where
    (Const a) == (Const b) = a == b
    (Pw a p) == (Pw b q) = a == b && p == q
    (Exp a p e) == (Exp b q f) = a == b && p == q && e == f
    (Trig a p t) == (Trig b q s) = a == b && p == q && t == s
    _ == _ = False

instance Evaluable Term where
    function (Const a) = \x -> getRounded (fromIntegral a)
    function (Pw i p) = \x -> getRounded ((fromIntegral i) * (function p x))   
    function (Exp i p e) = \x -> getRounded ((fromIntegral i) * (function p x) * (function e x)) 
    function (Trig i p t) = \x -> getRounded ((fromIntegral i) * (function p x) * (function t x))  

multiply m power (Const x) = Pw (m*x) power
multiply m (Power n) (Pw x (Power y)) = Pw (m*x) (Power (n+y))
multiply m (Power n) (Trig x (Power y) trig) = Trig (m*x) (Power (n+y)) trig
multiply m (Power n) (Exp x (Power y) exp) = Exp (m*x) (Power (n+y)) exp

instance Differentiable Term where
    derivative (Const _) = [Const 0]
    derivative (Pw _ (Power 0)) = [Const 0]
    derivative (Pw m (Power n)) = [Pw (m*n) (Power (n-1))]
    derivative (Trig m (Power n) trig) = result
        where derivatives = derivative trig
              productDerivative1 = Trig (m*n) (Power (n-1)) trig
              productDerivative2 = map (multiply m (Power n)) derivatives
              result = if n > 0 then productDerivative1:productDerivative2 else productDerivative2
    derivative (Exp m (Power n) exp) = result
        where derivatives = derivative exp
              productDerivative1 = Exp (m*n) (Power (n-1)) exp
              productDerivative2 = map(multiply m (Power n)) derivatives
              result = if n > 0 then productDerivative1:productDerivative2 else productDerivative2


-- INSTANCES FOR [TERM]

instance Evaluable [Term] where
    function [] = \x -> 0
    function (t:ts) = \x -> getRounded ((function t x) + (function ts x))

instance Differentiable [Term] where
    derivative [] = []
    derivative (t:ts) = combineTerms ((derivative t) ++ (derivative ts))

combineTerms :: [Term] -> [Term]    
combineTerms [] = []    
combineTerms (t:ts) = combineTerms' t (combineTerms ts)

combineTerms' :: Term -> [Term] -> [Term]
combineTerms' t [] = [t]
combineTerms' t (t':ts)
    | t `canCombineWith` t' = (addTerms t t') : ts
    | otherwise = t' : combineTerms' t ts

canCombineWith :: Term -> Term -> Bool
t `canCombineWith` t' = case (t, t') of
    (Const 0, _) -> True
    (_, Const 0) -> True
    (Const a, Const b) -> True
    (Exp i p e, Exp j q f) -> p == q && e == f
    (Pw i p, Pw j q) -> p == q
    (Trig i p t, Trig j q u) -> p == q && t == u
    _ -> False

addTerms :: Term -> Term -> Term    
addTerms (Const 0) t = t
addTerms t (Const 0) = t
addTerms (Const a) (Const b) = Const (a + b)
addTerms (Pw i p) (Pw j q) = if (p == q) then Pw (i + j) p else Pw i p
addTerms (Exp i p e) (Exp j q f) = if ((p == q) && (e == f)) then Exp (i + j) p e else Exp i p e
addTerms (Trig i p t) (Trig j q u) = if ((p == q) && (t == u)) then Trig (i + j) p t else Trig i p t
addTerms t t' = t

