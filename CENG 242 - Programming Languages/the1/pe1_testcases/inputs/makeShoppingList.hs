import PE1

stock1 = [("Tomato", 500.0), ("Cheese", 50), ("Butter", 10), ("Pasta", 250)]
stock2 = [("Cheese", 100.0), ("Butter", 250), ("Orange", 1000), ("Chocolate", 200), ("Bread", 500)]

toast = Recipe "Toast" [("Bread", 100), ("Cheese", 50), ("Butter", 25)]
tomatoPasta = Recipe "Tomato Pasta" [("Tomato", 500), ("Olive Oil", 10), ("Cheese", 50), ("Pasta", 250)]
friedEgg = Recipe "Fried Egg" [("Egg", 120), ("Butter", 25)]

prices1 = [Price "Tomato" 1000 12, Price "Potato" 1000 20, Price "Cheese" 500 50, Price "Flour" 1000 5, Price "Yeast" 10 2, Price "Bread" 400 10, Price "Butter" 100 5, Price "Pasta" 500 15, Price "Egg" 60 2,  Price "Olive Oil" 500 90]
prices2 = [Price "Tomato" 1000 10, Price "Potato" 1000 20, Price "Cheese" 250 50, Price "Flour" 1000 5, Price "Yeast" 10 2, Price "Bread" 400 10, Price "Butter" 100 25, Price "Pasta" 500 10, Price "Egg" 60 2, Price "Olive Oil" 500 90]

sl1 = makeShoppingList stock1 [toast, friedEgg] prices1
sl2 = makeShoppingList stock1 [tomatoPasta, friedEgg] prices1
sl3 = makeShoppingList stock1 [toast, tomatoPasta, friedEgg] prices2
sl4 = makeShoppingList stock2 [toast, tomatoPasta] prices2
sl5 = makeShoppingList stock2 [toast, friedEgg, tomatoPasta] prices2

main = do
    putStrLn (show sl1)
    putStrLn (show sl2)
    putStrLn (show sl3)
    putStrLn (show sl4)
    putStrLn (show sl5)
