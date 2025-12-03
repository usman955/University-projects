FAST NUCES Exam Scheduling using :-

APPROACH SUMMARY:
1. Modeling: The problem is solved as a Constraint Satisfaction Problem (CSP).
2. Logic: A weighted heuristic sorts courses by 'difficulty' (conflicts + size).
3. Optimization: A 'Hill Climbing' optimizer runs 3000 iterations to swap slots.
   It uses a cost function that applies infinite penalties to any student having 
   4 exams/day, forcing the algorithm to eliminate such cases.
