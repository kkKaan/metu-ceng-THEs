#Watch the youtube video to learn how to use it 
# Gokturk Ucoluk, METU, Dec 2020

from tkinter import *
import sys

WINDOW_MAXIMAL_WIDTH = 1200
WINDOW_MAXIMAL_HEIGHT= 1000
M=50   # actual values shall be read from command line
N=100

SCALE = min(WINDOW_MAXIMAL_WIDTH/N,WINDOW_MAXIMAL_HEIGHT/M)
RADIUS = max(1, SCALE//2)-1



root = Tk()
root.resizable(0,0)

My_Canvas = Canvas(root,bg = "white", width=N*SCALE, height=M*SCALE)


Mark_x = None
Mark_y = None
Last_x = None
Last_y = None
Line_item = None
Oval_item = None
Just_killed = False
In_color = "green"
Out_color = "green"
Created_individual_count = 0

def create_universe(m_row,n_column):
  universe = []
  single_row = [None]*n_column
  for j in range(0,m_row):
    universe.append(single_row.copy())
  return universe

def assign_individual_to_universe_position(individual,c,r): # i th Individual
  global Universe, Created_individual_count
  Universe[r][c] = individual
  Created_individual_count += 1

def canvas_to_universe(x_or_y):
  return round(x_or_y/SCALE)

def universe_to_canvas(c_or_r):
  return round(c_or_r*SCALE)

def approx_equal(num1,num2):
  return abs((num1-num2)/SCALE) < 0.2

def line_to_direction(start_x,start_y,end_x,end_y):
    if approx_equal(end_x,start_x):
      return (0 if end_y<start_y else 4)
    if approx_equal(end_y,start_y):
      return (6 if end_x<start_x else 2)
    if end_y<start_y:
      return (7 if end_x<start_x else 1)
    else:
      return (5 if end_x<start_x else 3)



Universe = create_universe(M,N)

def single_grid_dot(x,y):
  My_Canvas.create_oval(x-1,y-1,x+1,y+1,outline="gray", fill="white")


def draw_grid():
  for i in range(0,M):
    for j in range(0,N):
      single_grid_dot(round(j*SCALE),round(i*SCALE))


def marking(event):
  global Mark_x, Mark_y, Last_x, Last_y, Line_item, Oval_item, Just_killed, Created_individual_count
  if Mark_x == None:
    Mark_x,Mark_y = event.x,event.y
    # first, check from universe do we have a predefined entity here, if so delete it, also delete it from universe
    universe_row = canvas_to_universe(Mark_y)
    universe_col = canvas_to_universe(Mark_x)
    universe_content = Universe[universe_row][universe_col]
    if universe_content != None :
      My_Canvas.delete(universe_content["line_item"])
      My_Canvas.delete(universe_content["oval_item"])
      Universe[universe_row][universe_col] = None
      Created_individual_count -= 1
      Just_killed = True
      return
    else :
      Oval_item = My_Canvas.create_oval(Mark_x-RADIUS,Mark_y-RADIUS,Mark_x+RADIUS,Mark_y+RADIUS,outline=Out_color, fill=In_color)




def drawing(event):
  global Mark_x, Mark_y, Last_x, Last_y, Line_item, Oval_item, Just_killed
  if Just_killed: return
  else:
    if Last_x == None:
      Last_x,Last_y = event.x,event.y
      Line_item = My_Canvas.create_line(Mark_x,Mark_y,Last_x,Last_y)
    else:
      Last_x,Last_y = event.x,event.y
      My_Canvas.coords(Line_item,Mark_x,Mark_y,Last_x,Last_y)


def set_noinf_nomask(event):
  global In_color, Out_color
  Out_color = "green"
  In_color =  "green"
  Lbl_individual['text'] = "●"
  Lbl_individual['fg']   = "green"

def set_inf_nomask(event):
  global In_color, Out_color
  Out_color = "red"
  In_color =  "red"
  Lbl_individual['text'] = "●"
  Lbl_individual['fg']   = "red"

def set_noinf_mask(event):
  global In_color, Out_color
  Out_color = "green"
  In_color =  "white"
  Lbl_individual['text'] = "○"
  Lbl_individual['fg']   = "green"

def set_inf_mask(event):
  global In_color, Out_color
  Out_color = "red"
  In_color =  "white"
  Lbl_individual['text'] = "○"
  Lbl_individual['fg']   = "red"


def  end_of_mark(event):
  global Mark_x, Mark_y, Last_x, Last_y, Line_item, Oval_item, Just_killed
  global Lbl_quack, Created_individual_count
  global Out_color, In_color
  # register_individual()
  if not Just_killed :
    assign_individual_to_universe_position({"line_item":Line_item, "oval_item":Oval_item, \
                                          "direction":line_to_direction(Mark_x,Mark_y,Last_x,Last_y), \
                                          "mask":"masked" if In_color == "white" else "notmasked",
                                          "infection":"notinfected" if Out_color=="green" else "infected"} , \
                                         canvas_to_universe(Mark_x),canvas_to_universe(Mark_y))
  Lbl_quack['text'] = str(Created_individual_count)
  Just_killed = False
  Mark_x = None
  Mark_y = None
  Last_x = None
  Last_y = None
  Line_item = None
  Oval_item = None

def clearscrn():
  global Universe, Created_individual_count
  My_Canvas.delete("all")
  draw_grid()
  Universe = create_universe(M,N)
  Created_individual_count = 0

def save():
  global Universe
  file = open("pandemic-data.txt","w")
  file.write("[\n")
  for row in range(0,M):
    for col in range(0,N):
      if Universe[row][col]==None : continue
      individual = Universe[row][col]
      individual_state = [(col,row), individual['direction'], individual['mask'], individual['infection']]
      file.write(str(individual_state))
      file.write(" ,\n")
  file.write("]")
  file.close()

My_Canvas.pack()
draw_grid()


btn_clr = Button(root,text="clear all",command=clearscrn)
btn_clr.place(x=30, y=M*SCALE)
btn_save = Button(root,text="SAVE",command=save)
Lbl_quack = Label(root,text="0", font=("Arial",18))
Lbl_quack.place(x=100, y=M*SCALE)
Lbl_individual = Label(root,text="●", font=("Arial",28), fg="green")
Lbl_individual.place(x=150, y=M*SCALE-7)

btn_save.pack()
#btn_clr.pack()

My_Canvas.bind('<Button-1>',marking)
My_Canvas.bind('<B1-Motion>',drawing)
My_Canvas.bind('<ButtonRelease>',end_of_mark)
root.bind('<KeyPress-g>', set_noinf_nomask)
root.bind('<KeyPress-G>', set_noinf_mask)
root.bind('<KeyPress-r>', set_inf_nomask)
root.bind('<KeyPress-R>', set_inf_mask)

root.mainloop()




def main():
  global M, N
  if len(sys.argv) != 3:
    print ("Exactly two command line arguments have to be supplied to create_universe <row_count> <column_count>")
    exit(1)
  M = int(sys.argv[1])
  N = int(sys.argv[2])


if __name__ == '__main__':
  main()