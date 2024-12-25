#!/usr/bin/python3
import sys

toks = []

try:
    file_path = sys.argv[1]
except:
    file_path = None

class AST_Node:
    def __init__(self, node_type, children=None):
        self.node_type = node_type
        self.children = children if children is not None else []

def parse_tokens():
    if file_path:
        with open(file_path) as f:
            code = f.read()

            for char in code:
                if char in ['+', '-', '>', '<', '.', ',', '[', ']']:
                    toks.append(char)

def build_ast(tokens):
    #root = AST_Node("PROGRAM")
    root = AST_Node("ROOT")
    stack = [root]
    current = root

    for token in tokens:
        if token == "[":
            new_node = AST_Node("LOOP_L")
            current.children.append(new_node)
            stack.append(new_node)
            current = new_node
        elif token == "]":
            new_node = AST_Node("LOOP_R")
            current.children.append(new_node)
            stack.pop()
            current = stack[-1]
        else:
            new_node = AST_Node(token)
            current.children.append(new_node)
    
    return root

def print_ast(node, depth=0):
    print("  " * depth + node.node_type)
    for child in node.children:
        print_ast(child, depth + 1)

def compile_ast(root, loop_count=0):
    c = None

    for child in root.children:
        c = child

        if child.node_type == "LOOP_L":
            loop_count = compile_ast(c, loop_count + 1)
            print(f"\tcall\tL{loop_count}\n\n")
        
    #loop_count += 1
    return loop_count

# compile if file path is given
if __name__ == "__main__":
    if file_path:
        parse_tokens()
        ast = build_ast(toks)
        #print_ast(ast)
        compile_ast(ast)

    else:
        print("No file path given.")
