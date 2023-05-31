#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

struct InitialNode{
	InfoNode * info;
}

struct InfoNode{
	NumerationType numeration;
	TeamNode * team;
	FormationNode * formation;
	LineupNode * lineup;
	MetadataNode * metadata;
}

enum NumerationType{
	NUM,
	NONUM
}

struct TeamNode{
	TeamType teamType;
	char * teamName;
	int teamNumber;
}

enum TeamType{
	TEAMNAME,
	NOTEAMNAME
}

struct FormationNode{
	FormationNumberNode * formationNumber;
}

struct FormationNumberNode{
	FormationNumberType formationNumberType;
	char * formationNumber;
	FormationNumberNode * nextFormationNumber;
}

enum FormationNumberType{
	FINAL,
	NOFINAL
}

struct LineupNode{
	PlayerInfoNode * playerInfo;
	SubstitutesNode * substitutes;
}

struct PlayerInfoNode{
	char * playerName;
	int playerNumber;
	PlayerInfoNode * nextPlayerInfo;
}

struct SubstitutesNode{
	char * substituteName;
	int substituteNumber;
	SubstitutesNode * nextSubstitute;
}

struct LineupNoNumNode{
	PlayerInfoNoNumNode * playerInfoNoNum;
	SubstitutesNoNumNode * substitutesNoNum;
}

struct PlayerInfoNoNumNode{
	char * playerName;
	PlayerInfoNoNumNode * nextPlayerInfoNoNum;
}

struct SubstitutesNoNumNode{
	char * substituteName;
	SubstitutesNoNumNode * nextSubstituteNoNum;
}

struct MetadataNode{
	MetadataType metadataType;
	MatchDateNode * matchDate;
	MatchResultNode * matchResult;
}

enum MetadataType{
	DATE,
	RESULT,
	COMPLETE,
	EMPTY
}

struct MatchDateNode{
	char * date;
}

struct MatchResultNode{
	char * result;
}

#endif
