\documentclass{article}

\title{The2 Assignment: Simulation of Individual Movement and Infection}
\author{Your Name}
\date{\today}

\begin{document}

\maketitle

\section{Introduction}

This README file provides an overview and detailed explanation of the program for the "the2" assignment. The program simulates the movement of individuals on a grid while considering factors such as infection transmission, masks, and probabilities.

\section{Specifications}

The specifications for the "the2" assignment are as follows:

\begin{itemize}
    \item Individuals move in an order specified by their numbering.
    \item Each individual's move depends on their previous move and probability values.
    \item Infection transmission probability depends on the distance between individuals and is subject to a threshold value $D$.
    \item Individuals can wear masks, reducing infection transmission probability.
    \item The simulation progresses in time frames, with new positions and infection states computed for each individual.
    \item The \texttt{new\_move()} function returns the next time frame's universal state.
\end{itemize}

\section{Usage}

\begin{enumerate}
    \item Implement the \texttt{new\_move()} function in the \texttt{the2.py} file.
    \item Follow the given looping order to compute new positions and infection states.
    \item Ensure that the \texttt{get\_data()} function is available to retrieve input data.
    \item Do not alter the looping order to prevent corruption of the evaluation process.
    \item The program is designed to work within the constraints of concepts covered in lectures, without object-oriented programming.
\end{enumerate}

\section{Visualizations}

While the program includes visualization capabilities (\texttt{draw.py}), these are for visualization purposes only and are not part of the grading process. The provided visualization script can help you visualize your simulation results.

\section{How to Use \texttt{draw.py}}

\begin{itemize}
    \item Place \texttt{the2.py}, \texttt{draw.py}, and \texttt{evaluator.py} in your working directory.
    \item Run \texttt{draw.py} using Python. It imports \texttt{the2.py} and \texttt{evaluator.py}.
    \item Modify the \texttt{DELAY} variable in \texttt{draw.py} to adjust the delay between successive \texttt{new\_move()} calls.
    \item Note that \texttt{draw.py} uses a coordinate system with the origin at the top-left corner.
\end{itemize}

\section{Notes}

\begin{itemize}
    \item Implement the \texttt{new\_move()} function following the specifications provided.
    \item The input data is error-free and can be retrieved using the \texttt{get\_data()} function.
    \item Only import from the \texttt{math} and \texttt{random} modules. Do not import from other files/libraries.
    \item Make sure to adhere to the specified looping order and interaction rules.
\end{itemize}

\end{document}
