import PE1

toast = Recipe "Toast" [("Bread", 100), ("Cheese", 50), ("Butter", 25)]
tomatoPasta = Recipe "Tomato Pasta" [("Tomato", 500), ("Olive Oil", 10), ("Cheese", 50), ("Pasta", 250)]
friedEgg = Recipe "Fried Egg" [("Egg", 120), ("Butter", 25)]

prices1 = [Price "Tomato" 1000 12, Price "Potato" 1000 20, Price "Cheese" 500 50, Price "Flour" 1000 5, Price "Yeast" 10 2, Price "Bread" 400 10, Price "Butter" 100 5, Price "Pasta" 500 15, Price "Egg" 60 2,  Price "Olive Oil" 500 90]
prices2 = [Price "Tomato" 1000 10, Price "Potato" 1000 20, Price "Cheese" 250 50, Price "Flour" 1000 5, Price "Yeast" 10 2, Price "Bread" 400 10, Price "Butter" 100 25, Price "Pasta" 500 10, Price "Egg" 60 2, Price "Olive Oil" 500 90]

cost1 = recipeCost toast prices1
cost2 = recipeCost tomatoPasta prices1
cost3 = recipeCost friedEgg prices1
cost4 = recipeCost tomatoPasta prices2
cost5 = recipeCost toast prices2

main = do
    putStrLn (show cost1)
    putStrLn (show cost2)
    putStrLn (show cost3)
    putStrLn (show cost4)
    putStrLn (show cost5)
