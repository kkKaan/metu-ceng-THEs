import Text.Printf
import Data.List

-- Type synonyms --
type Point = (Double, Double)
type Signal = (Double, Double, Double, Double)

-- This function takes a Double and rounds it to 2 decimal places as requested in the PE --
getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

getDistance :: Point -> Point -> Double

getDistance (x1, y1) (x2, y2) = getRounded (sqrt (((x2 - x1)^2) + ((y2 - y1)^2)))

-------------------------------------------------------------------------------------------

findAllDistances :: Point -> [Point] -> [Double]

findAllDistances _ [] = []
findAllDistances b (a:r) = (getDistance b a) : findAllDistances b r 

-------------------------------------------------------------------------------------------

findExtremes :: Point -> [Point] -> (Point, Point)

findMyIndex element [] ind = ind
findMyIndex element (a:list) ind 
    | a == element = ind 
    | otherwise = findMyIndex element list (ind + 1)

findExtremes b (a:[]) = (a,a)
findExtremes b l = let distList = findAllDistances b l
                       minIndex = findMyIndex (minimum distList) distList 0
                       maxIndex = findMyIndex (maximum distList) distList 0
                    in ((l !! minIndex),(l !! maxIndex))

-------------------------------------------------------------------------------------------

mkList (a,b,c,d) = [a,b,c,d]

getSingleAction :: Signal -> String

getSingleAction signal = trueSignal (mkList signal)
    where
        trueSignal [a,b,c,d]
            | ((c - a) > 0) && (d - b == 0) = "South"
            | ((c - a) < 0) && (d - b == 0) = "North"
            | ((c - a) == 0) && (d - b > 0) = "West"
            | ((c - a) == 0) && (d - b < 0) = "East"
            | ((c - a) > 0) && (d - b > 0) = "SouthWest"
            | ((c - a) < 0) && (d - b > 0) = "NorthWest"
            | ((c - a) > 0) && (d - b < 0) = "SouthEast"
            | ((c - a) < 0) && (d - b < 0) = "NorthEast"
            | otherwise = "Stay"

-------------------------------------------------------------------------------------------

getAllActions :: [Signal] -> [String]

getAllActions [] = []
getAllActions (a:signals) = (getSingleAction a) : getAllActions signals  

-------------------------------------------------------------------------------------------

numberOfGivenAction :: Num a => [Signal] -> String -> a

numberOfGivenAction signals action = 
    let actList = filter (== action) (getAllActions signals)
    in fromIntegral (length actList)
