module PE1 where

import Text.Printf

-- PE1: Recipe Calculator
-- The premise of this homework if to write a recipe calculator that
-- calculates: how much a recipe costs to make, what can be made with the
-- ingredients already available, and how much extra ingredients need to
-- be bought in order to make a recipe.

-- Recipe = Recipe Name [(Ingredient, Quantity)]
data Recipe = Recipe String [(String, Double)] deriving Show

-- Price = Price Ingredient Quantity Price
data Price = Price String Double Double deriving Show

-- You can use this as-is
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x
               
-- getPriceName :: Price -> String
-- getPriceName (Price name _ _) = name

-- getPriceQuantity :: Price -> Double
-- getPriceQuantity (Price _ quantity _) = quantity

getPricePrice :: Price -> Double
getPricePrice (Price _ _ price) = price

getRoundedStock :: [(String, Double)] -> [(String, Double)]
getRoundedStock stock = [(name, getRounded amount) | (name, amount) <- stock, getRounded amount > 0]

-- Calculate how much the given amount of the given ingredient costs
getIngredientCost :: (String, Double) -> [Price] -> Double
getIngredientCost (ingredientName, quantity) prices =
    let matchingPrice = head (filter (\(Price name _ _) -> name == ingredientName) prices)
        amoFin = (\(Price _ pri _) -> quantity / pri) matchingPrice
    in getRounded (amoFin * (getPricePrice matchingPrice))

-- Calculate how much it costs to buy all the ingredients of a recipe
recipeCost :: Recipe -> [Price] -> Double
recipeCost (Recipe _ ingredients) prices = getRounded (sum (map (\x -> getIngredientCost x prices) ingredients))

-- Given a list of how much you already have of each ingredient,
-- calculate how much of which ingredients are missing for a recipe
missingIngredients :: Recipe -> [(String, Double)] -> [(String, Double)]
missingIngredients (Recipe _ ingredients) stock = 
    finList
        where 
            matched = [(name1, getRounded (amount1 - amount2)) | (name1, amount1) <- ingredients, (name2, amount2) <- stock, (name1 == name2) && (getRounded (amount1 - amount2) > 0)]
            otherIng = [(name1, getRounded amount1) | (name1, amount1) <- ingredients, (name1 `notElem` (map fst matched)) && (name1 `notElem` (map fst stock)) && (getRounded amount1 > 0)]
            finList = matched ++ otherIng


-- Given a list of ingredients in your kitchen, calculate what you would
-- have left after making the given recipe. If there isn't enough of an
-- ingredient, the recipe cannot be made! You shouldn't change the amount
-- of ingredient in that case.
makeRecipe :: [(String, Double)] -> Recipe -> [(String, Double)]
makeRecipe stock (Recipe _ ingredients) =
    if missingIngredients (Recipe "" ingredients) stock == []
        then finList 
    else getRoundedStock stock
    where 
        matched = [(name1, getRounded (amount1 - amount2)) | (name1, amount1) <- stock, (name2, amount2) <- ingredients, (name1 == name2) && (getRounded (amount1 - amount2) > 0)]
        otherIng = [(name1, getRounded amount1) | (name1, amount1) <- stock, (name1 `notElem` (map fst matched)) && (name1 `notElem` (map fst ingredients)) && (getRounded amount1 > 0)]
        finList = matched ++ otherIng
        
        
-- Given a list of ingredients you already have, and a list of recipes,
-- make a shopping list showing how much of each ingredient you need
-- to buy, and its cost. Each ingredient mush appear in the shopping list
-- at most once (no duplicates!).
combineItems items = combineItems' [] items
    where
        combineItems' acc [] = acc
        combineItems' acc (xs:xss) =
            let
                acc' = foldl combineItem acc xs
            in
            combineItems' acc' xss

        combineItem [] y = [y]
        combineItem (x:xs) y
            | fst x == fst y = (fst x, snd x + snd y) : xs
            | otherwise = x : combineItem xs y

combineRecipes recipes = combineItems (map (\(Recipe _ ingredients) -> ingredients) recipes)

makeShoppingList :: [(String, Double)] -> [Recipe] -> [Price] -> [(String, Double, Double)]
makeShoppingList stock recipes prices = 
    let allNeededItems = combineRecipes recipes
        itemsInStock = [(name1, getRounded amount2) | (name1, amount1) <- allNeededItems, (name2, amount2) <- stock, (name1 == name2) && (getRounded amount2 > 0)]
        needForRecipes = [(name1, getRounded (amount1 - amount2)) | (name1, amount1) <- allNeededItems, (name2, amount2) <- itemsInStock, (name1 == name2) && (getRounded (amount1 - amount2) > 0)] ++ [(name1, amount1) | (name1, amount1) <- allNeededItems, (name1 `notElem` (map fst itemsInStock)) && (getRounded amount1 > 0)]
        finalList = [(name, amount, getIngredientCost (name, amount) prices) | (name, amount) <- needForRecipes]
    in finalList
    
    
    