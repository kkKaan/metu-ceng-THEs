import PE1

stock1 = [("Tomato", 500.0), ("Cheese", 50), ("Butter", 10), ("Pasta", 250)]
stock2 = [("Cheese", 100.0), ("Butter", 250), ("Orange", 1000), ("Chocolate", 200), ("Bread", 500)]

toast = Recipe "Toast" [("Bread", 100), ("Cheese", 50), ("Butter", 25)]
tomatoPasta = Recipe "Tomato Pasta" [("Tomato", 500), ("Olive Oil", 10), ("Cheese", 50), ("Pasta", 250)]
friedEgg = Recipe "Fried Egg" [("Egg", 120), ("Butter", 25)]

ings1 = missingIngredients toast stock1
ings2 = missingIngredients toast stock2
ings3 = missingIngredients tomatoPasta stock1
ings4 = missingIngredients friedEgg stock2
ings5 = missingIngredients tomatoPasta stock2

main = do
    putStrLn (show ings1)
    putStrLn (show ings2)
    putStrLn (show ings3)
    putStrLn (show ings4)
    putStrLn (show ings5)
