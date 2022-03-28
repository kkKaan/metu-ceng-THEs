import math
import random
from evaluator import *   

moves = [0,1,2,3,4,5,6,7]
constants = get_data()[:6]
people = get_data()[6]

def new_move(): # This is the function to be evaluated, and just calling the main function with the data from the given function "get_data()".
    return new_move_helper(people)

def new_move_helper(people_list):

    p_index, population = 0, 0  # "p_index" is people index and a counter for next_moves list. 
    next_moves, next_positions, universal_state, positions_dict = [], [], [], {}

    # The probabilities defined in the pdf of the homework.
    prob_green = constants[-1] / 2 
    prob_yellow = constants[-1] / 8
    prob_blue = ( 1-constants[-1] - constants[-1] ** 2 ) / 2
    prob_purple = (2 * (constants[-1] ** 2)) / 5
    prob_gray = (constants[-1] ** 2) / 5
    
    for person in people_list:
        move_list = moves[person[1]:] + moves[:person[1]] # This line, and the loop, is a shortcut, it reduces the number of lines of code by adjusting the order of the movement types in a list with the weights of them.
        next_move = random.choices(move_list, weights = [prob_green, prob_yellow, prob_blue, prob_purple, prob_gray, prob_purple, prob_blue, prob_yellow]) 
        next_moves.append(next_move[0])

    for movement in next_moves: # This loop is finding the next positions, but not certain since they may not move due to the related coordinates are full, of the each person. 

        if movement == 0: # The if statement is to determine the next point this person will be, according to the movement code. 
            next_p = (people_list[p_index][0][0], people_list[p_index][0][1]+1) if people_list[p_index][0][1]+1 < constants[0] else (people_list[p_index][0][0], people_list[p_index][0][1]) 
        elif movement == 1:
            next_p = (people_list[p_index][0][0]-1, people_list[p_index][0][1]+1) if people_list[p_index][0][0]-1 >= 0 and people_list[p_index][0][1]+1 < constants[0] else (people_list[p_index][0][0], people_list[p_index][0][1]) 
        elif movement == 2:
            next_p = (people_list[p_index][0][0]-1, people_list[p_index][0][1]) if people_list[p_index][0][0]-1 >= 0 else (people_list[p_index][0][0], people_list[p_index][0][1]) 
        elif movement == 3:
            next_p = (people_list[p_index][0][0]-1, people_list[p_index][0][1]-1) if people_list[p_index][0][0]-1 >= 0 and people_list[p_index][0][1]-1 >= 0 else (people_list[p_index][0][0], people_list[p_index][0][1]) 
        elif movement == 4:
            next_p = (people_list[p_index][0][0], people_list[p_index][0][1]-1) if people_list[p_index][0][1]-1 >= 0 else (people_list[p_index][0][0], people_list[p_index][0][1]) 
        elif movement == 5:
            next_p = (people_list[p_index][0][0]+1, people_list[p_index][0][1]-1) if people_list[p_index][0][0]+1 < constants[1] and people_list[p_index][0][1]-1 >= 0 else (people_list[p_index][0][0], people_list[p_index][0][1])
        elif movement == 6:
            next_p = (people_list[p_index][0][0]+1, people_list[p_index][0][1]) if people_list[p_index][0][0]+1 < constants[1] else (people_list[p_index][0][0], people_list[p_index][0][1]) 
        elif movement == 7:
            next_p=(people_list[p_index][0][0]+1, people_list[p_index][0][1]+1) if people_list[p_index][0][0]+1 < constants[1] and people_list[p_index][0][1]+1 < constants[0] else (people_list[p_index][0][0], people_list[p_index][0][1])
        
        other_points = next_positions[:p_index] + [k[0] for k in people_list[p_index + 1:]]  # A short definition for the other points than the person whose next position is just calculated.

        if next_p in other_points: # Checks if this is a full one, if it is, it changes next_p to its previous value.
            next_p = (people_list[p_index][0][0], people_list[p_index][0][1])

        if next_p == (people_list[p_index][0][0], people_list[p_index][0][1]): # It checks if the previous if statement was evaluated, and undo the changes on the next_moves list.  
            next_moves[p_index] = people_list[p_index][1]

        next_positions.append(next_p)
        p_index += 1

    for i in people_list:
        positions_dict[str(i)] = i[-1]

    # This part is for finding the infection status, and update them according to the each person's position.
    for individual in people_list:

        if people_list.index(individual)+1 < len(people_list):

            for theSecond in people_list[people_list.index(individual)+1:]:

                distance = math.sqrt( ( next_positions[people_list.index(individual)][1] - next_positions[people_list.index(theSecond)][1] )**2 + \
                                      ( next_positions[people_list.index(individual)][0] - next_positions[people_list.index(theSecond)][0] )**2 )
                
                prob_of_inf = min(1, constants[3] / distance**2)

                if individual[-1] == theSecond[-1]:
                    continue
                else:
                    if distance <= constants[2]:
                        if individual[2] == "notmasked" and theSecond[2] == "notmasked":
                            prob_of_inf = min(1, constants[3] / distance**2)*1
                        elif individual[2] == "notmasked" and theSecond[2] == "masked" or individual[2] == "masked" and theSecond[2] == "notmasked": 
                            prob_of_inf /= constants[4]
                        else:
                            prob_of_inf /= (constants[4])**2

                        next_stat = random.choices(["infected", "notinfected"], weights = [prob_of_inf, 1-prob_of_inf])

                        if individual[-1] == "infected":
                            if positions_dict[str(theSecond)] == "infected":
                                continue
                            else:
                                positions_dict[str(theSecond)] = next_stat[0]
                        else:
                            if positions_dict[str(individual)] == "infected":
                                continue
                            else:
                                positions_dict[str(individual)] = next_stat[0]
                    else:
                        continue # Writing this for all of these continue statements I wrote, they may not be necessary, but they are helpful for understanding of the code, I think. 
        else:
            break

    for p in people_list: # Updates the universal state of the population.
        universal_state.append( [next_positions[population], next_moves[population], p[2], list(positions_dict.values())[population]] ) 
        population+=1

    global people
    people=universal_state
    return universal_state 
