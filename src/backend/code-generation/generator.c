#include "generator.h"


static FILE * pythonFile;

char* getPlayersArray() {
    char* resultBuffer = calloc(1, BUFFER_LENGTH * sizeof(char));
    symbol_t* symbolTable = getSymbolTable();
    CList* playerList = symbolTable->players;
    for (int i = 0; i < playerList->count(playerList)-1; i++) {
        player_t* player = playerList->at(playerList, i);
        int playerNumber = player->number;
        char* playerName = player->name;
        if (playerNumber == -1)
            sprintf(resultBuffer + strlen(resultBuffer), "{\"number\": NULL, \"name\": \"%s\"},", playerName);
        else {
            sprintf(resultBuffer + strlen(resultBuffer), "{\"number\": \"%d\", \"name\": \"%s\"},", playerNumber,playerName);
        }
    }
    player_t* player = playerList->at(playerList, playerList->count(playerList)-1);
    if (player->number == -1)
        sprintf(resultBuffer + strlen(resultBuffer), "{\"number\": NULL, \"name\": \"%s\"}", player->name);
    else {
        sprintf(resultBuffer + strlen(resultBuffer), "{\"number\": \"%d\", \"name\": \"%s\"}", player->number,player->name);
    }
    return resultBuffer;
}

char* getMatchResult(InitialNode* initial) {
    MatchResultNode* matchResult = initial->info->metadata->matchResult;
    if (matchResult == NULL) {
        return strdup("");
    }
    return strdup(matchResult->result);
}

char* getMatchDate(InitialNode* initial) {
    MatchDateNode* matchDate = initial->info->metadata->matchDate;
    if (matchDate == NULL) {
        return strdup("");
    }
    return strdup(matchDate->date);
}

char* getTeamName(InitialNode* initial) {
    char* teamName = initial->info->team->teamName;
    if (teamName == NULL) {
        return strdup("");
    }
    return strdup(teamName);
}

char* getSubstitutesArray() {
    char* resultBuffer = calloc(1, BUFFER_LENGTH * sizeof(char));
    symbol_t* symbolTable = getSymbolTable();
    CList* subsList = symbolTable->subs;
    for (int i = 0; i < subsList->count(subsList)-1; i++) {
        player_t* player = subsList->at(subsList, i);
        int playerNumber = player->number;
        char* playerName = player->name;
        if (playerNumber == -1)
            sprintf(resultBuffer + strlen(resultBuffer), "{\"number\": NULL, \"name\": \"%s\"},", playerName);
        else {
            sprintf(resultBuffer + strlen(resultBuffer), "{\"number\": \"%d\", \"name\": \"%s\"},", playerNumber,playerName);
        }
    }
    player_t* player = subsList->at(subsList, subsList->count(subsList)-1);
    if (player->number == -1)
        sprintf(resultBuffer + strlen(resultBuffer), "{\"number\": NULL, \"name\": \"%s\"}", player->name);
    else {
        sprintf(resultBuffer + strlen(resultBuffer), "{\"number\": \"%d\", \"name\": \"%s\"}", player->number,player->name);
    }
    return resultBuffer;
}

char* getFormationsArray() {
    char* result1Buffer = calloc(1, BUFFER_LENGTH * sizeof(char));
    symbol_t* symbolTable = getSymbolTable();
    CList* formationList = symbolTable->formations;
    for (int i = 0; i < formationList->count(formationList)-1; i++) {
        char* formation = formationList->at(formationList, i);
        sprintf(result1Buffer + strlen(result1Buffer), "\"%s\",", formation);
    }
    char* formation = formationList->at(formationList, formationList->count(formationList)-1);
    sprintf(result1Buffer + strlen(result1Buffer), "\"%s\"", formation);
    return result1Buffer;
}

void Generator(InitialNode * initial) {
	pythonFile = fopen("imageGenerator.py", "w");



    fprintf(pythonFile, "from PIL import Image, ImageFont, ImageDraw\n");

    char * playersArray = getPlayersArray();
    fprintf(pythonFile,"players = [%s]\n", playersArray);
    free(playersArray);
    char * matchResult = getMatchResult(initial);
    fprintf(pythonFile, "match_result = '%s'\n",matchResult);
    free(matchResult);
    char * matchDate = getMatchDate(initial);
    fprintf(pythonFile, "match_date = %s\n",matchDate);
    free(matchDate);
    char * teamName = getTeamName(initial);
    fprintf(pythonFile, "team_name = %s\n",teamName);
    free(teamName);
    char * substitutesArray = getSubstitutesArray();
    fprintf(pythonFile, "substitutes = [%s]\n",substitutesArray);
    free(substitutesArray);
    char * formationsArray = getFormationsArray();
    fprintf(pythonFile, "formations = [%s]\n",formationsArray);
    free(formationsArray);

    fprintf(pythonFile, "for formation in formations:\n");
    fprintf(pythonFile, "\tformationQty = formation.split(\"-\")\n"
                        "\tdefenseNumber = int(formationQty[0])\n"
                        "\tmidfieldNumber = int(formationQty[1])\n"
                        "\tattackNumber = int(formationQty[2])\n");
    fprintf(pythonFile,"\tpitch_image = Image.open(\"resources/field.png\").convert(\"RGBA\")\n"
                       "\tjersey_image = Image.open(\"resources/jersey.png\").convert(\"RGBA\")\n"
                       "\twhite_image = Image.open(\"resources/white.jpg\").convert(\"RGBA\")\n"
                       "\tjersey_width, jersey_height = jersey_image.size\n"
                       "\tjersey_size = (int(jersey_width * 0.45), int(jersey_height * 0.45))\n"
                       "\tjersey_image = jersey_image.resize(jersey_size)\n" );
    fprintf(pythonFile,"\tdraw = ImageDraw.Draw(pitch_image)\n"
                       "\tfont = ImageFont.truetype(\"arial.ttf\", 40)  # Change the font and size as needed\n"
                       "\tfont2 = ImageFont.truetype(\"arial.ttf\", 25)\n"
                       "\ttitle_font = ImageFont.truetype(\"arialbd.ttf\", 70)\n"
                       "\tsubstitutes_font = ImageFont.truetype(\"arial.ttf\", 20)\n"
                       "\tfont_thickness = 3\n"
                       "\tresult_font = ImageFont.truetype(\"arial.ttf\", 70)\n");
    fprintf(pythonFile, "\tt = 10\n"
                        "\n"
                        "\tImageDraw.Draw(white_image).text((white_image.width / 3, t), \"Substitutes\",\n"
                        "                                     fill=(0, 0, 0), font=title_font)\n"
                        "\n"
                        "\tt = 110\n");
    fprintf(pythonFile, "\tfor sub in substitutes:\n"
                        "\t\tif sub[\"number\"] != \"\":\n"
                        "\t\t\tImageDraw.Draw(white_image).text((white_image.width / 3, t), sub[\"number\"] + \" : \" + sub[\"name\"],\n"
                        "                                             fill=(0, 0, 0), font=substitutes_font)\n"
                        "\t\telse:\n"
                        "\t\t\tImageDraw.Draw(white_image).text((white_image.width / 3, t), sub[\"name\"],\n"
                        "                                             fill=(0, 0, 0), font=substitutes_font)\n"
                        "\t\tt = t + 50\n");
    fprintf(pythonFile,"\tt += 20\n"
                       "\n"
                       "\tif match_result != \"\" and t < 1200:\n"
                       "\t\tImageDraw.Draw(white_image).text((white_image.width / 3, t), \"Match Result:\",\n"
                       "                                         fill=(0, 0, 0), font=title_font)\n"
                       "\t\tt += 80\n"
                       "\t\tImageDraw.Draw(white_image).text((white_image.width / 3, t), match_result,\n"
                       "                                         fill=(0, 0, 0), font=result_font)\n"
                       "\n"
                       "\tt += 150\n");
    fprintf(pythonFile, "\tif match_date != \"\" and t < 1200:\n"
                        "\t\tImageDraw.Draw(white_image).text((white_image.width / 3, t), \"Match Date:\",\n"
                        "                                         fill=(0, 0, 0), font=title_font)\n"
                        "\t\tt += 80\n"
                        "\t\tImageDraw.Draw(white_image).text((white_image.width / 3, t), match_date,\n"
                        "                                         fill=(0, 0, 0), font=result_font)\n");
    fprintf(pythonFile, "\tdef draw_jersey(player, position):\n"
                        "\t\t# Paste the jersey\n"
                        "\t\tpitch_image.paste(jersey_image, position, jersey_image)\n"
                        "\n"
                        "\t\t# Calculate the center position for the number\n"
                        "\n"
                        "\t\t# Add the number\n"
                        "\t\tnumber_x = 90 if int(player[\"number\"]) >= 10 else 100\n"
                        "\t\tdraw.text((position[0] + number_x, position[1] + 70), player[\"number\"], fill=(255, 255, 255), font=font, stroke_width=font_thickness,\n"
                        "                  stroke_fill=(0, 0, 0))\n"
                        "\n"
                        "\t\t# Add the name\n"
                        "\t\tdraw.text((position[0]+50, position[1]+180), player[\"name\"], fill=(255, 255, 255), font=font2)\n");
    fprintf(pythonFile, "\tu = 10\n"
                        "\n"
                        "\tif team_name != \"\":\n"
                        "\t\tImageDraw.Draw(pitch_image).text((pitch_image.width / 3, u), team_name,\n"
                        "                                         fill=(0, 0, 0), font=title_font)\n"
                        "\t\tu += 100\n"
                        "\t\tImageDraw.Draw(pitch_image).text((pitch_image.width / 3, u), formation,\n"
                        "                                         fill=(0, 0, 0), font=font)\n");
    fprintf(pythonFile, "\t#Draw goalkeeper\n"
                        "\tposition = (325, 1075)\n"
                        "\tplayer = players[0]\n"
                        "\tdraw_jersey(player, position)");
    fprintf(pythonFile, "\t# Draw defending players\n"
                        "\tfor i in range(defenseNumber):\n"
                        "\t\tplayer = players[i + 1]\n"
                        "\t\tif defenseNumber == 4:\n"
                        "\t\t\tstartPosition = 30\n"
                        "\t\telif defenseNumber == 3:\n"
                        "\t\t\tstartPosition = 120\n"
                        "\t\telse:\n"
                        "\t\t\tstartPosition = 150\n"
                        "\n"
                        "\t\tposition = (startPosition + i * 210, 850)\n"
                        "\t\tdraw_jersey(player, position)\n");
    fprintf(pythonFile, "# Draw midfielding players\n"
                        "\tfor i in range(defenseNumber, defenseNumber+midfieldNumber):\n"
                        "\t\tplayer = players[i+1]\n"
                        "\t\tif midfieldNumber == 4:\n"
                        "\t\t\tstartPosition = 30\n"
                        "\t\telif midfieldNumber ==3:\n"
                        "\t\t\tstartPosition = 120\n"
                        "\t\telse:\n"
                        "\t\t\tstartPosition = 150\n"
                        "\n"
                        "\t\tposition = (startPosition + (i-(defenseNumber)) * 210, 600)\n"
                        "\t\tdraw_jersey(player, position)");
    fprintf(pythonFile, "\t# Draw attacking players\n"
                        "\tfor i in range(defenseNumber + midfieldNumber, defenseNumber + midfieldNumber + attackNumber):\n"
                        "\t\tplayer = players[i+1]\n"
                        "\t\tif attackNumber == 4:\n"
                        "\t\t\tstartPosition = 30\n"
                        "\t\telif attackNumber == 3:\n"
                        "\t\t\tstartPosition = 100\n"
                        "\t\telse:\n"
                        "\t\t\tstartPosition = 150\n"
                        "\t\tposition = (100 + (i-(defenseNumber+midfieldNumber)) * 210, 300)  # Adjust the vertical position as needed\n"
                        "\t\tdraw_jersey(player, position)\n");
    fprintf(pythonFile, "\tfinal_image = Image.new('RGB', (pitch_image.width + white_image.width, pitch_image.height))\n"
                        "\tfinal_image.paste(pitch_image, (0, 0))\n"
                        "\tfinal_image.paste(white_image, (pitch_image.width, 0))\n"
                        "\n"
                        "\t# Display the resulting image\n"
                        "\tfinal_image.show()\n"
                        "\n"
                        "\t# Save the resulting image\n"
                        "\tfinal_image.save(f\"result_{formation}.png\")\n");

    fclose(pythonFile);

}
