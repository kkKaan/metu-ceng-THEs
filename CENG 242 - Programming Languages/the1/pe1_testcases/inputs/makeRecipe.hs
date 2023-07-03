import PE1

stock1 = [("Tomato", 500.0), ("Cheese", 50), ("Butter", 10), ("Pasta", 250)]
stock2 = [("Cheese", 100.0), ("Butter", 250), ("Orange", 1000), ("Chocolate", 200), ("Bread", 500)]

toast = Recipe "Toast" [("Bread", 100), ("Cheese", 50), ("Butter", 25)]
tomatoPasta = Recipe "Tomato Pasta" [("Tomato", 500), ("Olive Oil", 10), ("Cheese", 50), ("Pasta", 250)]
friedEgg = Recipe "Fried Egg" [("Egg", 120), ("Butter", 25)]

rem1 = makeRecipe stock1 toast
rem2 = makeRecipe stock2 toast
rem3 = makeRecipe stock1 friedEgg
rem4 = makeRecipe stock1 tomatoPasta
rem5 = makeRecipe stock2 tomatoPasta

main = do
    putStrLn (show rem1)
    putStrLn (show rem2)
    putStrLn (show rem3)
    putStrLn (show rem4)
    putStrLn (show rem5)
