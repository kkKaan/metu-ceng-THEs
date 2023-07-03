import PE1

gic1 = getIngredientCost ("Tomato", 300) [Price "Tomato" 1000 20]
gic2 = getIngredientCost ("Tomato", 250) [Price "Potato" 1000 30, Price "Tomato" 1000 20]
gic3 = getIngredientCost ("Butter", 400) [Price "Potato" 1000 30, Price "Butter" 100 8, Price "Tomato" 1000 20]
gic4 = getIngredientCost ("Spaghetti", 200) [Price "Penne" 500 10, Price "Gnocchi" 500 50, Price "Spaghetti" 500 12]
gic5 = getIngredientCost ("Mince", 500) [Price "Mince" 1000 200]

main = do
    putStrLn (show gic1)
    putStrLn (show gic2)
    putStrLn (show gic3)
    putStrLn (show gic4)
    putStrLn (show gic5)
