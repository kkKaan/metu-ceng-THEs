:- module(main, [is_vote_wasted/2, is_candidate_elected/2, candidate_count_from_city/3, all_parties/1, all_candidates_from_party/2, all_elected_from_party/2, election_rate/2, council_percentage/2, alternative_debate_setups/2]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

is_vote_wasted(City, Party) :-
    \+ elected(City, Party, _).

is_candidate_elected(Name, PoliticalParty) :-
    candidate(Name, PoliticalParty, City, Row),
    elected(City, PoliticalParty, ElectedRepresentativeCount),
    Row =< ElectedRepresentativeCount.    

candidate_count_from_city([], _, 0).    
candidate_count_from_city([Candidate|RestOfCandidates], GivenCity, Count) :- % if match
    candidate(Candidate, _, GivenCity, _),
    candidate_count_from_city(RestOfCandidates, GivenCity, RestOfCount),
    Count is RestOfCount + 1.
candidate_count_from_city([Candidate|RestOfCandidates], GivenCity, Count) :- % if no match
    \+ candidate(Candidate, _, GivenCity, _),
    candidate_count_from_city(RestOfCandidates, GivenCity, Count). 


all_parties(ListOfPoliticalParties) :-
    findall(Party, party(Party, _), ListOfPoliticalParties).

all_candidates_from_party(PoliticalParty, ListOfCandidates) :-
    findall(Candidate, candidate(Candidate, PoliticalParty, _, _), ListOfCandidates).

all_elected_from_party(PoliticalParty, ListOfCandidates) :-
    findall(Candidate, (candidate(Candidate, PoliticalParty, _, _), is_candidate_elected(Candidate, PoliticalParty)), ListOfCandidates).

election_rate(PoliticalParty, Percentage) :-
    all_candidates_from_party(PoliticalParty, ListOfCandidates),
    all_elected_from_party(PoliticalParty, ListOfElected),
    length(ListOfCandidates, CandidateCount),
    length(ListOfElected, ElectedCount),
    Percentage is ElectedCount / CandidateCount.

council_percentage(PoliticalParty, Percentage) :-
    all_elected_from_party(PoliticalParty, ListOfElected),
    all_elected_from_party(_, ListOfAllElected),
    length(ListOfElected, ElectedCount),
    length(ListOfAllElected, AllElectedCount),
    Percentage is ElectedCount / AllElectedCount.

alternative_debate_setups(DescriptionString, OrderedListOfCandidates) :-
    string_chars(DescriptionString, PartyInitials), % convert string to list of chars
    find_and_permute(PartyInitials, [], OrderedListOfCandidates).

find_and_permute([], _, []).
find_and_permute([PartyInitial|Rest], UsedBefore, [Candidate|CandidateList]) :-
    party(PartyName, PartyInitial), 
    find_candidate(Candidate, PartyName, UsedBefore), % find a candidate that is not used before
    find_and_permute(Rest, [Candidate|UsedBefore], CandidateList). % find the rest of the candidates

find_candidate(Candidate, PartyName, UsedBefore) :-
    candidate(Candidate, PartyName, _, _),
    \+ member(Candidate, UsedBefore). % check if candidate is not used before
    
    
    