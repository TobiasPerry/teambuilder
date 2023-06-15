#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

typedef struct FormationNumberNode FormationNumberNode;
typedef struct PlayerInfoNode PlayerInfoNode;
typedef struct SubstitutesNode SubstitutesNode;
typedef struct PlayerInfoNoNumNode PlayerInfoNoNumNode;
typedef struct SubstitutesNoNumNode SubstitutesNoNumNode;
typedef struct LineupNode LineupNode;
typedef struct LineupNoNumNode LineupNoNumNode;
typedef struct InfoNode InfoNode;
typedef struct TeamNode TeamNode;
typedef struct FormationNode FormationNode;
typedef struct MetadataNode MetadataNode;
typedef struct MatchDateNode MatchDateNode;
typedef struct MatchResultNode MatchResultNode;
typedef struct InitialNode InitialNode;
typedef struct InfoNoNumNode InfoNoNumNode;
typedef struct SubInfoNode SubInfoNode;
typedef struct SubInfoNoNumNode SubInfoNoNumNode;


typedef enum{
	NUM,
	NONUM
}NumerationType;

typedef enum {
	TEAMNAME,
	NOTEAMNAME
}TeamType;

typedef enum{
	FINAL,
	NOFINAL
}FormationNumberType;

typedef enum {
	HASDATE,
	HASRESULT,
	COMPLETE,
	EMPTY
} MetadataType;


struct InitialNode{
	InfoNode * info;
};

struct InfoNode{
	NumerationType numeration;
	TeamNode * team;
	FormationNode * formation;
	LineupNode * lineup;
	MetadataNode * metadata;
};

struct InfoNoNumNode{
	NumerationType numeration;
	TeamNode * team;
	FormationNode * formation;
	LineupNoNumNode * lineupNoNum;
	MetadataNode * metadata;
};

struct TeamNode{
	TeamType teamType;
	char * teamName;
	int teamNumber;
};

struct FormationNode{
	FormationNumberNode * formationNumber;
};

struct FormationNumberNode{
	FormationNumberType formationNumberType;
	char * formationNumber;
	FormationNumberNode * nextFormationNumber;
};

struct LineupNode{
	PlayerInfoNode * playerInfo;
	SubstitutesNode * substitutes;
};

struct PlayerInfoNode{
	char * playerName;
	int playerNumber;
	PlayerInfoNode * nextPlayerInfo;
};

struct SubstitutesNode{
	char * substituteName;
	int substituteNumber;
	SubstitutesNode * nextSubstitute;
};

struct SubInfoNode{
	char * substituteName;
	int substituteNumber;
	SubInfoNode * nextSubstitute;
};

struct SubInfoNoNumNode{
	char * substituteName;
	SubInfoNoNumNode * nextSubstitute;
};

struct LineupNoNumNode{
	PlayerInfoNoNumNode * playerInfoNoNum;
	SubstitutesNoNumNode * substitutesNoNum;
};

struct PlayerInfoNoNumNode{
	char * playerName;
	PlayerInfoNoNumNode * nextPlayerInfoNoNum;
};

struct SubstitutesNoNumNode{
	char * substituteName;
	SubstitutesNoNumNode * nextSubstituteNoNum;
};

struct MetadataNode{
	MetadataType metadataType;
	MatchDateNode * matchDate;
	MatchResultNode * matchResult;
};

struct MatchDateNode{
	char * date;
};

struct MatchResultNode{
	char * result;
};

#endif
