import PE3

show1 = show (Power 3)
show2 = show (Polynomial [(3, Power 2), (2, Power 0)])
show3 = show (Exponential (Polynomial [(3, Power 3), (4, Power 1)]))
show4 = show (Sin (Polynomial [(2, Power 1), (1, Power 0)]))
show5 = show (Trig 2 (Power 1) (Cos (Polynomial [(1, Power 1)])))
eq1 = show (Power 2 == Power 2)
ord1 = show (Power 4 <= Power 3)

main = do
    putStrLn show1
    putStrLn show2
    putStrLn show3
    putStrLn show4
    putStrLn show5
    putStrLn eq1
    putStrLn ord1
