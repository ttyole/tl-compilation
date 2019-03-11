./parser_generator -g expr_grammar.g -pc expr_parser.c -ph expr_parser.h -pdir expr table.html
cd expr
make
cd tests
for file in ./*.e
do
    echo "$file"
    ../cstar -c "$file" -show-ast "../../graphs/$file.dot"
    dot -Tpng ../../graphs/$file.dot -o ../../graphs/$file.png
done