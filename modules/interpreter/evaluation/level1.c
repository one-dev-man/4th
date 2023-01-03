#include "../../../includes/interpreter/evaluation/level1.h"

// 

#include <stdio.h>

// 

#include "../../../includes/utils/logger.h"

#include "../../../includes/utils/strutil.h"
#include "../../../includes/utils/fileutil.h"

#include "../../../includes/lecture.h"
#include "../../../includes/pile.h"

#include "../../../includes/interpreter/evaluation/operations.h"

#include "../../../includes/interpreter/locale.h"

// 

int EVALUATE_LEVEL_1(Programme prog, int included_word_start, int excluded_word_end, Pile eval_context_stack) {
    int eval_word_count = MEDIUM_LANGUAGE_WORD_COUNT;

    // 

    const char** eval_words = LANGUAGE_WORDS;

    // 

    int eval_status = EVALUATION_SUCCESS;

    // 

    char* word;
    bool is_int;
    int n;
    
    for(int i = included_word_start; i < excluded_word_end && eval_status == EVALUATION_SUCCESS; ++i) {
        word = MotProg(prog, i);

        //

        n = str2int(word, &is_int); 

        if(is_int)
            EvalEmpiler(eval_context_stack, n, &eval_status);
        else if(strArrayIncludes((char**) eval_words, 0, eval_word_count, word)) {
            // word == ".s"
            if(strEquals(word, (char*) eval_words[0]))
                EVAL_DOT_S(eval_context_stack);
            // word == "."
            else if(strEquals(word, (char*) eval_words[1]))
                EVAL_DOT(eval_context_stack, &eval_status);
            // word == "dup"
            else if(strEquals(word, (char*) eval_words[2]))
                EVAL_DUP(eval_context_stack, &eval_status);
            // word == "drop"
            else if(strEquals(word, (char*) eval_words[3]))
                EVAL_DROP(eval_context_stack, &eval_status);
            // word == "swap"
            else if(strEquals(word, (char*) eval_words[4]))
                EVAL_SWAP(eval_context_stack, &eval_status);
            // word == "over"
            else if(strEquals(word, (char*) eval_words[5]))
                EVAL_OVER(eval_context_stack, &eval_status);

            // 

            // word == "+"
            else if(strEquals(word, (char*) eval_words[6]))
                EVAL_ARITHMETICAL_OPERATION(eval_context_stack, ARITHMETICAL_OPERATION_ADD, &eval_status);
            // word == "-"
            else if(strEquals(word, (char*) eval_words[7]))
                EVAL_ARITHMETICAL_OPERATION(eval_context_stack, ARITHMETICAL_OPERATION_SUBSTRACT, &eval_status);
            // word == "*"
            else if(strEquals(word, (char*) eval_words[8]))
                EVAL_ARITHMETICAL_OPERATION(eval_context_stack, ARITHMETICAL_OPERATION_MULTIPLY, &eval_status);
            // word == "/"
            else if(strEquals(word, (char*) eval_words[9]))
                EVAL_ARITHMETICAL_OPERATION(eval_context_stack, ARITHMETICAL_OPERATION_DIVIDE, &eval_status);
            // word == "%"
            else if(strEquals(word, (char*) eval_words[10]))
                EVAL_ARITHMETICAL_OPERATION(eval_context_stack, ARITHMETICAL_OPERATION_MODULO, &eval_status);

            //

            // word == "="
            else if(strEquals(word, (char*) eval_words[11]))
                EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_EQUAL, &eval_status);
            // word == "<"
            else if(strEquals(word, (char*) eval_words[12]))
                EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_LESSER, &eval_status);
            // word == "<="
            else if(strEquals(word, (char*) eval_words[13]))
                EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_LESSER_OR_EQUAL, &eval_status);
            // word == ">"
            else if(strEquals(word, (char*) eval_words[14]))
                EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_GREATER, &eval_status);
            // word == ">="
            else if(strEquals(word, (char*) eval_words[15]))
                EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_GREATER_OR_EQUAL, &eval_status);
            // word == "and"
            else if(strEquals(word, (char*) eval_words[16]))
                EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_AND, &eval_status);
            // word == "or"
            else if(strEquals(word, (char*) eval_words[17]))
                EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_OR, &eval_status);
            // word == "not"
            else if(strEquals(word, (char*) eval_words[18]))
                EVAL_LOGICAL_OPERATION(eval_context_stack, LOGICAL_OPERATION_NOT, &eval_status);
        }
        else {
            fprintf(stderr, (char*) logger->error("Word `%s` not supported by this interpreter level."), word);
            eval_status = EVALUATION_ERROR_NOT_SUPPORTED_WORD;
        }
    }

    // 

    return eval_status;
}

// 

