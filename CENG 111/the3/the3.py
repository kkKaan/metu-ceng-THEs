# Created by Kaan Karaçanta, 2021

# This function creates nested lists and gives the tree's final form.
def tree_creator(x):
    if len(x) == 1:
        return x[0]

    for k in x[1:]: # This 2d loop is, simply, inserting the elements at the end to the previous ones' inside by matching them. 
        if type(k[1]) == float:
            continue

        for m in k[1:]:
            if m[1] == x[0][0]:
                x[x.index(k)][k.index(m)] = [x[x.index(k)][k.index(m)][0], x[0]]
                return tree_creator(x[1:])
            continue
    return tree_creator(x[1:])   

# This function finds the root from an unordered list with the specifications given in the homework
def rootFinder(y):
    a = [k[:] for k in y] # I could not find anything simple for that variable's name, parts maybe.
    names = []
    others = []

    for part in a: # Finds the root by the specifications of the homework
        if type(part[1]) == float:
            others += part
        else:
            names.append(part[0])
            others+=[k[1] for k in part[1:]]

    filtered = list(filter(lambda x: type(x) == str, others))

    for rooty in names:
        if rooty not in filtered:
            for m in a:
                if m[0] == rooty:
                    a.remove(m)
                    a.insert(0, m)
    return a

# This function should be called after we find the root. Besides, this gives the list a order (outermost level to the innermost but not exactly).
def makeTheRootFirst(lst, pre_tree, a):
    if pre_tree == []:
        pre_tree.append(lst[0])
        return makeTheRootFirst(lst[1:], pre_tree, 0)

    if a == len(pre_tree):
        return pre_tree

    for i in pre_tree[a][1:]: # It prepares the pre-final version of the tree by adding the elements starting from the first children of the root. 
        if type(i) == float:
            continue

        for k in lst:
            if k[0] == i[1]:
                pre_tree.append(k)
                lst.remove(k)
                break
            continue    
    return makeTheRootFirst(lst, pre_tree, a+1)


# These following 3 functions are doing the things they are supposed to do, which are explained in detail in the homework.
def calculate_price(part_list):
    root = rootFinder(part_list)
    formed_list = makeTheRootFirst(root,[],0)
    tree = tree_creator(formed_list[::-1])
    n = [1]
    n.append(tree)

    def fHelp(trees,total,summ):
        for k in trees[1][1:]:
            if type(k) == float:
                return k
            total += [k[0] * (fHelp(k,[],summ))]

        total = [sum(total)]
        summ = total[:][0]
        return summ

    return fHelp(n,[],0)

def required_parts(part_list):
    root = rootFinder(part_list)
    formed_list = makeTheRootFirst(root,[],0)
    tree = tree_creator(formed_list[::-1])
    n = [1]
    n.append(tree)
    stack = []

    def helper(treeE,how_many):
        for k in treeE[1][1:]:
            if type(k)==float:
                stack.append((how_many*treeE[0], treeE[1][0]))
                continue
            helper(k, how_many * treeE[0])
        return stack

    return helper(n,1)

def stock_check(part_list,stock_list):
    parts = required_parts(part_list)
    stock_names = [a[1] for a in stock_list]

    def finder(parts,stock_list,needs):
        for i in parts:
            if i[1] not in stock_names:
                needs.append((i[1],i[0]))
                continue
                
            for k in stock_list:
                if i[1] == k[1] and i[0] == k[0]:
                    break
                elif i[1] == k[1] and i[0] != k[0]:
                    if i[0] - k[0] > 0:
                        needs.append(( i[1], i[0] - k[0] ))
                    else:
                        break
        return needs

    return finder(parts,stock_list,[])
