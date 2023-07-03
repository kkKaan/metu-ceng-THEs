% CHANGES DONE TO THIS FILE WILL BE OVERWRITTEN. 
% IT WILL HAVE NO EFFECT ON YOUR GRADE.

:- module(kb, [party/2, candidate/4, elected/3, to_elect/1]).
% party(PoliticalParty, Initial).
% candidate(Name, PoliticalParty, City, Row).
% elected(City, PoliticalParty, ElectedRepresentativeCount).
% to_elect(RepresentativeCount).

party(peoples_parks_party, p).
party(peoples_wealth_party, w).
party(dentists_wealth_party, d).

candidate(leslie_knope, peoples_parks_party, pawnee, 1).
candidate(ben_wyatt, peoples_parks_party, pawnee, 2).
candidate(april_ludgate, peoples_parks_party, pawnee, 3).
candidate(tom_haverford, peoples_parks_party, pawnee, 4).
candidate(jerry_gerwich, peoples_parks_party, pawnee, 5).
candidate(jeremy_jamm, dentists_wealth_party, pawnee, 1).
candidate(joe_fantringham, peoples_wealth_party, pawnee, 1).
candidate(bill_dexhart, peoples_wealth_party, pawnee, 2).
candidate(craig_middlebrooks, peoples_parks_party, eagleton, 1).
candidate(douglass_howser, peoples_parks_party, eagleton, 2).
candidate(ingrid_de_forest, peoples_wealth_party, eagleton, 1).
candidate(lindsay_carlisle_shay, peoples_wealth_party, eagleton, 2).
candidate(george_gernway, peoples_wealth_party, eagleton, 3).
candidate(joan_callamezzo, peoples_wealth_party, eagleton, 4).

elected(pawnee, peoples_parks_party, 4).
elected(eagleton, peoples_wealth_party, 4).
elected(eagleton, peoples_parks_party, 2).

to_elect(10).