digraph G {
n1 [label="pair"]
n2 [label="pair"]
n3 [label="a_simple_variable"]
n2 -> n3 [label="0"]
n4 [label="pair"]
n5 [label="0"]
n4 -> n5 [label="0"]
n6 [label="8"]
n4 -> n6 [label="1"]
n2 -> n4 [label="1"]
n1 -> n2 [label="0"]
n7 [label="triple"]
n8 [label="3"]
n7 -> n8 [label="0"]
n9 [label="a_simple_variable"]
n7 -> n9 [label="1"]
n10 [label="triple"]
n11 [label="3"]
n10 -> n11 [label="0"]
n12 [label="pair"]
n13 [label="0"]
n12 -> n13 [label="0"]
n14 [label="5"]
n12 -> n14 [label="1"]
n10 -> n12 [label="1"]
n15 [label="pair"]
n16 [label="0"]
n15 -> n16 [label="0"]
n17 [label="3"]
n15 -> n17 [label="1"]
n10 -> n15 [label="2"]
n7 -> n10 [label="2"]
n1 -> n7 [label="1"]
}