#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

typedef struct FormationNumberNode FormationNumberNode;
typedef struct PlayerInfoNode PlayerInfoNode;
typedef struct SubstitutesNode SubstitutesNode;
typedef struct PlayerInfoNoNumNode PlayerInfoNoNumNode;
typedef struct SubstitutesNoNumNode SubstitutesNoNumNode;

enum NumerationType{
	NUM,
	NONUM
}

enum TeamType{
	TEAMNAME,
	NOTEAMNAME
}

enum FormationNumberType{
	FINAL,
	NOFINAL
}

enum MetadataType{
	DATE,
	RESULT,
	COMPLETE,
	EMPTY
}


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

struct TeamNode{
	TeamType teamType;
	char * teamName;
	int teamNumber;
}

struct FormationNode{
	FormationNumberNode * formationNumber;
}

struct FormationNumberNode{
	FormationNumberType formationNumberType;
	char * formationNumber;
	FormationNumberNode * nextFormationNumber;
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
