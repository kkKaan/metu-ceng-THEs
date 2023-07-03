# 
# YOU CAN PLAY AROUND WITH  "DELAY".
# OTHERWISE, YOU SHOULDN'T UPDATE THIS FILE.
# DO NOT SEND THIS FILE TO US.
#
from math import *
from tkinter import *
from evaluator import *
from the2 import *   # provides the new_move() which is called in move_individuals()


DELAY = 1000 # that is the default value, can be changed. It is in [miliseconds]

WINDOW_MAXIMAL_WIDTH = 1000
WINDOW_MAXIMAL_HEIGHT= 800

DATA = get_data()     # comes from evaluator.py

[M,N,D,KAPPA,LAMBDA,MU] = DATA[:6]

SCALE = min(WINDOW_MAXIMAL_WIDTH/N,WINDOW_MAXIMAL_HEIGHT/M)

WINDOW_STEP = round(SCALE)
RADIUS = max(1, SCALE//2)

def draw_individual(canv,x,y,rad,out_color,in_color):
	"""DO NOT MODIFY THIS FUNCTION"""
	return canv.create_oval((x-rad),(y-rad),(x+rad),(y+rad),width=1, outline=out_color, fill=in_color)

def redraw_individual(canv,item,x,y,rad,out_color,in_color):
    """DO NOT MODIFY THIS FUNCTION"""
    canv.itemconfig(item,outline=out_color, fill=in_color)
    canv.coords(item,(x-rad),(y-rad),(x+rad),(y+rad))

def draw_legend(canvas): 
  def draw_one(canvas, X, Y, outline, fill, text):
    canvas.create_oval(X-RADIUS, Y-RADIUS, X+RADIUS, Y+RADIUS, width=1, outline=outline, fill=fill)
    canvas.create_text(X+2*RADIUS+RADIUS, Y, anchor=W, font="Purisa", text=text)
  
  draw_one(canvas, 3+RADIUS, 3+RADIUS,   "red", "white", "Masked & Infected")
  draw_one(canvas, 3+RADIUS, 3+RADIUS*4, "green", "white", "Masked & Not Infected")
  draw_one(canvas, 3+RADIUS, 3+RADIUS*7, "red", "red", "Not Masked & Infected")
  draw_one(canvas, 3+RADIUS, 3+RADIUS*10, "green", "green", "Not Masked & Not Infected")

def draw_individuals(): #inialization of _individuals
    """DO NOT MODIFY THIS FUNCTION"""    
    global My_canvas, My__individuals, DATA, RADIUS, SCALE, DELAY
    My__individuals=[]   # hold tctk entities
    for [(x,y),last_move,mask_status, infection_status]  in DATA[6:][0]:
        center_x = int(x*SCALE)
        center_y = int(y*SCALE)
        out_color = "red" if infection_status=="infected" else "green"
        in_color = out_color if mask_status=="notmasked" else "white"
        My__individuals.append(draw_individual(My_canvas,center_x,center_y,RADIUS,out_color,in_color))
    draw_legend(My_canvas)
    My_canvas.after(DELAY,callback)

def move_individuals():
    """DO NOT MODIFY THIS FUNCTION"""    
    global My__individuals, My_canvas
    new_universe = new_move() # the2.py  provides new_move()
    for i,[(x,y), last_move,mask_status, infection_status] in enumerate(new_universe):
        new_center_x = x*SCALE
        new_center_y = y*SCALE
        new_out_color = "red" if infection_status=="infected" else "green"
        new_in_color = new_out_color if mask_status=="notmasked" else "white"
        redraw_individual(My_canvas, My__individuals[i], new_center_x, new_center_y, RADIUS, new_out_color, new_in_color)
        
def callback():
    """DO NOT MODIFY THIS FUNCTION"""    
    global My_canvas,DELAY
    move_individuals()
    My_canvas.after(DELAY,callback)
        
Master = Tk()

My_canvas = Canvas(Master, width=N*SCALE, height=M*SCALE)

My_canvas.pack()
draw_individuals()

Master.mainloop()
