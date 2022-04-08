import Text.Printf

type Point = (Int, Int)
type Dimensions = (Int, Int)
type Vector = (Int, Int)

getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

castIntToDouble x = (fromIntegral x) :: Double

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------
getVector :: String -> Vector

getVector d 
    | d == "North" = (0,1)
    | d == "NorthEast" = (1,1)
    | d == "East" = (1,0)
    | d == "SouthEast" = (1,-1)    
    | d == "South" = (0,-1)
    | d == "SouthWest" = (-1,-1)
    | d == "West" = (-1,0)
    | d == "NorthWest" = (-1,1)
    | otherwise = (0,0)
    

-------------------------------------------------------------------------------------------------------------------------------
getAllVectors :: [String] -> [Vector]

getAllVectors [] = []
getAllVectors (a:lst) = getVector a : getAllVectors lst

-------------------------------------------------------------------------------------------------------------------------------

producePath :: Point -> [String] -> [Point]

producePath initial actions = initial : (helper initial actionVec)
    where 
        actionVec = getAllVectors actions
        helper _ [] = []
        helper (x,y) ((a,b):lst) = (x+a, y+b) : helper (x+a, y+b) (lst)  
    
-------------------------------------------------------------------------------------------------------------------------------
takePathInArea :: [Point] -> Dimensions -> [Point]

takePathInArea [] (bx, by) = []
takePathInArea ((a,b):path) (bx, by) 
    | (a >= bx) || (b >= by) || (a < 0) || (b < 0) = []
    | otherwise = (a,b) : takePathInArea path (bx,by)

-------------------------------------------------------------------------------------------------------------------------------

remainingObjects :: [Point] -> Dimensions -> [Point] -> [Point]

remainingObjects path border objects = remain
    where 
        possiblePath = takePathInArea path border
        remain = [x | x <- objects, not (x `elem` possiblePath)]

-------------------------------------------------------------------------------------------------------------------------------
averageStepsInSuccess :: [[Point]] -> Dimensions -> [Point] -> Double

averageStepsInSuccess paths border objects = getRounded ((castIntToDouble noSteps) / (castIntToDouble noSuccPaths))
    where 
        succPaths = [ x | x <- paths, (remainingObjects x border objects == []) && (length x == length (takePathInArea x border))]
        stepLenOfPaths = [ length x | x <- succPaths]
        noSteps = sum stepLenOfPaths
        noSuccPaths = length succPaths
        -- noSuccPaths = length [ x | x <- paths, length (remainingObjects x border objects) == 0]











