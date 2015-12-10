(* ::Package:: *)

TestFunc[x_,y_]:=Sin[Pi * y / x] * Cos[Pi * x / y] * Exp[-1 * x / y];
Plot3D[TestFunc[x,y],{x,0,20},{y,0,20},PlotRange->Full]
NMinimize[{TestFunc[x,y],0.01<x<=20,0.01<y<=20},{x,y},Method->"DifferentialEvolution",MaxIterations->100]
NMinimize[{TestFunc[x,y],0.01<x<=20,0.01<y<=20},{x,y},Method->"RandomSearch",MaxIterations->100]
NMinimize[{TestFunc[x,y],0.01<x<=20,0.01<y<=20},{x,y},Method->"SimulatedAnnealing",MaxIterations->100]
NMinimize[{TestFunc[x,y],0.01<x<=20,0.01<y<=20},{x,y},Method->"NelderMead",MaxIterations->100]

TestFunc2[x_,y_] = Exp[Sin[50*x]] + Sin[60 * Exp[y]] + Sin[70 * Sin[x]] + Sin[Sin[80*y]]-Sin[10 (x+y)]+1/4 (x^2+y^2);
Plot3D[TestFunc2[x,y],{x,-1,1},{y,-1,1},Mesh->False,PlotRange->Full,PlotPoints->50]
NMinimize[{TestFunc2[x,y],-1<x<=1,-1<y<=1},{x,y},Method->"DifferentialEvolution",MaxIterations->100]
NMinimize[{TestFunc2[x,y],-1<x<=1,-1<y<=1},{x,y},Method->"RandomSearch",MaxIterations->100]
NMinimize[{TestFunc2[x,y],-1<x<=1,-1<y<=1},{x,y},Method->"SimulatedAnnealing",MaxIterations->100]
NMinimize[{TestFunc2[x,y],-1<x<=1,-1<y<=1},{x,y},Method->"NelderMead",MaxIterations->100]



