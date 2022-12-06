% set ft=prolog
% 3 constrains:
% 	each box has numbers 1 - 9
% 	each row that numbers 1 - 9
% 	each column has numbers 1 - 9
%
% 	Use one "box checker" to ensure that all numbers one through 9 exist
% 	and there are exactly  9 values
%
% 	"loop" over rows, cols, and boxes

% maybe check every possible number and pass the remainder on?

% sort box first, then pass to box
%
% 835416927296857431417293658569134782123678549748529163652781394981345276374962815
% [8,3,5,4,1,6,9,2,7,2,9,6,8,5,7,4,3,1,4,1,7,2,9,3,6,5,8,5,6,9,1,3,4,7,8,2,1,2,3,6,7,8,5,4,9,7,4,8,5,2,9,1,6,3,6,5,2,7,8,1,3,9,4,9,8,1,3,4,5,2,7,6,3,7,4,9,6,2,8,1,5]

%:- pack_install(list_util).
%:- (prolog_pack:current_pack(list_util) -> true ; pack_install(list_util)).
:- use_module(library(list_util)).

% takes a sorted list and ensures they contain all numbers from 1 to 9
s_box([1, 2, 3, 4, 5, 6, 7, 8, 9]).

% takes an unsorted list and ensures it contains all the numbers from 1 to 9
box(L) :-
	msort(L, S),
	s_box(S).

% ensures that every row of the input contains a box()
row9([N1, N2, N3, N4, N5, N6, N7, N8, N9 | T]) :-
	box([N1,N2,N3,N4,N5,N6,N7,N8,N9]),
	T = [],
	!.
row9([N1, N2, N3, N4, N5, N6, N7, N8, N9 | T]) :-
	box([N1,N2,N3,N4,N5,N6,N7,N8,N9]),
	row9(T).

% splits the board into 9 lists consisting of every 9th element starting from 0..8
split9([N1, N2, N3, N4, N5, N6, N7, N8, N9], [N1], [N2], [N3], [N4], [N5], [N6], [N7], [N8], [N9]) :- !.
split9([N1, N2, N3, N4, N5, N6, N7, N8, N9 | T], [N1|L1], [N2|L2], [N3|L3], [N4|L4], [N5|L5], [N6|L6], [N7|L7], [N8|L8], [N9|L9]) :-
	split9(T, L1, L2, L3, L4, L5, L6, L7, L8, L9).

col9(I) :-
	split9(I, L1, L2, L3, L4, L5, L6, L7, L8, L9),
	box(L1),
	box(L2),
	box(L3),
	box(L4),
	box(L5),
	box(L6),
	box(L7),
	box(L8),
	box(L9).

% takes an array that begins with a square's base and ensures the 9 elements make up a box()
helper_square(L) :-
	nth0(0, L, E0),
	nth0(1, L, E1),
	nth0(2, L, E2),
	nth0(9, L, E3),
	nth0(10, L, E4),
	nth0(11, L, E5),
	nth0(18, L, E6),
	nth0(19, L, E7),
	nth0(20, L, E8),
	box([E0, E1, E2, E3, E4, E5, E6, E7, E8]).


all_square(L) :-
	drop(L, 0, L1), helper_square(L1),
	drop(L, 3, L2), helper_square(L2),
	drop(L, 6, L3), helper_square(L3),
	drop(L, 27, L4), helper_square(L4),
	drop(L, 30, L5), helper_square(L5),
	drop(L, 33, L6), helper_square(L6),
	drop(L, 54, L7), helper_square(L7),
	drop(L, 57, L8), helper_square(L8),
	drop(L, 60, L9), helper_square(L9).

sudoku(I) :-
	length(I, 81),
	row9(I),
	col9(I),
	all_square(I).
