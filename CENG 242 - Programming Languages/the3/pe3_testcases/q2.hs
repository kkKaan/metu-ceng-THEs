import PE3

eval1 = show (function (Power 2) 3)
eval2 = show (function (Polynomial [(1, Power 2), (1, Power 0)]) 2)
eval3 = show (function (Exponential (Polynomial [(3, Power 3)])) 1)
eval4 = show (function (Cos (Polynomial [(3, Power 3)])) 1)
eval5 = show (function (Pw 2 (Power 2)) 2)
diff1 = show (derivative (Power 2))
diff2 = show (derivative (Polynomial [(1, Power 2), (1, Power 0)]))
diff3 = show (derivative (Exponential (Polynomial [(3, Power 3)])))
diff4 = show (derivative (Cos (Polynomial [(3, Power 3)])))
diff5 = show (derivative (Pw 2 (Power 2)))

main = do
    putStrLn eval1
    putStrLn eval2
    putStrLn eval3
    putStrLn eval4
    putStrLn eval5
    putStrLn diff1
    putStrLn diff2
    putStrLn diff3
    putStrLn diff4
    putStrLn diff5
