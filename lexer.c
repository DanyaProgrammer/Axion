#include "lexer.h"

#include <string.h>
#include <ctype.h>

int get_token() {
    register char* tmp;

    while (*prog == ' ' || *prog == '\t' || *prog == '\n' || *prog == '\0') {
	    prog++;
    }

    if (*prog == '\0') {
        return (tok = TOKEN_ENDFILE);
    }

    if (*prog == ';') {
	    return (tok = TOKEN_ENDCOMMAND);
    }

    if (isdigit(*prog) || *prog == '.') {
        int is_floater = 0;
        while (isdigit(*prog) || *prog == '.') {
            if (*prog == '.') {
                if (is_floater) {
                    return (tok = TOKEN_EOF);
                } else {
                    is_floater = 1;
                }
            }

            *tmp = *prog;
            tmp++;
            prog++;
        }

        *tmp = 0x00;

        if (is_floater) {
            return (tok = TOKEN_CONST_FLT);
        } else {
            return (tok = TOKEN_CONST_INT);
        }
    }

    if (strchr("+-*/%<>!|&^()[]{}=", *prog)) {
	while (strchr("+-*/%!|&^=", *prog)) {
		*tmp = *prog;
		prog++;
		tmp++;
	}

	*tmp = 0x00;

	if (!strcmp(buf, "+")) {
		return (tok = TOKEN_OPERATOR_ADD);
	} else if (!strcmp(buf, "-")) {
		return (tok = TOKEN_OPERATOR_SUB);
	} else if (!strcmp(buf, "*")) {
		return (tok = TOKEN_OPERATOR_MUL);
	} else if (!strcmp(buf, "/")) {
		return (tok = TOKEN_OPERATOR_DIV);
	} else if (!strcmp(buf, "&")) {
		return (tok = TOKEN_LOGIC_OPERATOR_AND);
	} else if (!strcmp(buf, "|")) {
		return (tok = TOKEN_LOGIC_OPERATOR_OR);
	} else if (!strcmp(buf, "^")) {
		return (tok = TOKEN_LOGIC_OPERATOR_XOR);
	} else if (!strcmp(buf, "!")) {
		return (tok = TOKEN_LOGIC_OPERATOR_NOT);
	} else if (!strcmp(buf, "&&")) {
		return (tok = TOKEN_BIT_OPERATOR_AND);
	} else if (!strcmp(buf, "||")) {
		return (tok = TOKEN_BIT_OPERATOR_OR);
	} else if (!strcmp(buf, "^^")) {
		return (tok = TOKEN_BIT_OPERATOR_XOR);
	} else if (!strcmp(buf, "!!")) {
		return (tok = TOKEN_BIT_OPERATOR_NOT);
	} else if (!strcmp(buf, "<<")) {
		return (tok = TOKEN_BIT_OPERATOR_LS);
	} else if (!strcmp(buf, ">>")) {
		return (tok = TOKEN_BIT_OPERATOR_RS);
	} else if (!strcmp(buf, "<")) {
		return (tok = TOKEN_LOGIC_OPERATOR_LT);
	} else if (!strcmp(buf, ">")) {
		return (tok = TOKEN_LOGIC_OPERATOR_GT);
	} else if (!strcmp(buf, "<=")) {
		return (tok = TOKEN_LOGIC_OPERATOR_LTET);
	} else if (!strcmp(buf, ">=")) {
		return (tok = TOKEN_LOGIC_OPERATOR_GTET);
	} else if (!strcmp(buf, "==")) {
		return (tok = TOKEN_LOGIC_OPERATOR_EQUALITY);
	} else if (!strcmp(buf, "!=")) {
		return (tok = TOKEN_LOGIC_OPERATOR_NOT_EQUAL);
	} else if (!strcmp(buf, "(")) {
		return (tok = TOKEN_LPAR);
	} else if (!strcmp(buf, ")")) {
		return (tok = TOKEN_RPAR);
	} else if (!strcmp(buf, "[")) {
		return (tok = TOKEN_LSQB);
	} else if (!strcmp(buf, "]")) {
		return (tok = TOKEN_RSQB);
	} else if (!strcmp(buf, "{")) {
		return (tok = TOKEN_LCBR);
	} else if (!strcmp(buf, "}")) {
		return (tok = TOKEN_RCBR);
	} else if (!strcmp(buf, "++")) {
		return (tok = TOKEN_OPERATOR_INC);
	} else if (!strcmp(buf, "--")) {
		return (tok = TOKEN_OPERATOR_DEC);
	} else {
		return (tok = TOKEN_EOF);
	}
}

    if (isalpha(*prog) || *prog == '_') {
        while (isalnum(*prog) || *prog == '_') {
            *tmp = *prog;
            tmp++;
            prog++;
        }

        *tmp = 0x00;

        if (!strcmp(buf, "i8")) {
            return (tok = TOKEN_TYPE_I8);
        } else if (!strcmp(buf, "i16")) {
            return (tok = TOKEN_TYPE_I16);
        } else if (!strcmp(buf, "i32")) {
            return (tok = TOKEN_TYPE_I32);
        } else if (!strcmp(buf, "i64")) {
            return (tok = TOKEN_TYPE_I64);
        } else if (!strcmp(buf, "u8")) {
            return (tok = TOKEN_TYPE_U8);
        } else if (!strcmp(buf, "u16")) {
            return (tok = TOKEN_TYPE_U16);
        } else if (!strcmp(buf, "u32")) {
            return (tok = TOKEN_TYPE_U32);
        } else if (!strcmp(buf, "u64")) {
            return (tok = TOKEN_TYPE_U64);
        } else if (!strcmp(buf, "f8")) {
            return (tok = TOKEN_TYPE_F8);
        } else if (!strcmp(buf, "f16")) {
            return (tok = TOKEN_TYPE_F16);
        } else if (!strcmp(buf, "f32")) {
            return (tok = TOKEN_TYPE_F32);
        } else if (!strcmp(buf, "f64")) {
            return (tok = TOKEN_TYPE_F64);
        } else if (!strcmp(buf, "chr")) {
            return (tok = TOKEN_TYPE_CHR);
        } else if (!strcmp(buf, "str")) {
            return (tok = TOKEN_TYPE_STR);
        } else if (!strcmp(buf, "cls")) {
            return (tok = TOKEN_TYPE_CLS);
        } else if (!strcmp(buf, "fnc")) {
            return (tok = TOKEN_TYPE_FNC);
        } else if (!strcmp(buf, "extern")) {
            return (tok = TOKEN_COMMAND_EXTERN);
        } else if (!strcmp(buf, "if")) {
            return (tok = TOKEN_COMMAND_IF);
        } else if (!strcmp(buf, "elif")) {
            return (tok = TOKEN_COMMAND_ELIF);
        } else if (!strcmp(buf, "else")) {
            return (tok = TOKEN_COMMAND_ELSE);
        } else if (!strcmp(buf, "while")) {
            return (tok = TOKEN_COMMAND_WHILE);
        } else if (!strcmp(buf, "for")) {
            return (tok = TOKEN_COMMAND_FOR);
        } else {
            return (tok = TOKEN_VAR);
        }
    }

    if (*prog == '"') {
        prog++;
        while (*prog != '"' && *prog != '\r' && *prog != '\n' && *prog != '\0') {
            *tmp++ = *prog++;
        }

        if (*prog == '\r' || *prog == '\n' || *prog == '\0') {
            return (tok = TOKEN_EOF);
        }

        prog++;
        *tmp = 0x00;

        return (tok = TOKEN_CONST_STR);
    }

    if (*prog == '\'') {
        prog++;
        if (*prog == '\r' || *prog == '\n' || *prog == '\0') {
            return (tok = TOKEN_EOF);
        }

        *tmp++ = *prog++;
        if (*prog != '\'') {
            return (tok = TOKEN_EOF);
        }
        prog++;
        *tmp = 0x00;

        return (tok = TOKEN_CONST_CHR);
    }

    return (tok = TOKEN_EOF);
}

void put_back() {
    register char* tmp = buf;
    while (*tmp) {
        prog--;
        tmp++;
    }
}