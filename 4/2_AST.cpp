// 抽象语法树 Abstract Syntax Tree
// 是源代码或表达式的抽象语法结构的树状表现形式
// 每个结点表示源代码中的一种结构

// 抽象是因为不会表示出真实语法的每个细节
// 比如嵌套隐含在树结构中
// if语句可以用两个分支结点表示

// 对于二元表达式, 孩子结点既可以是数字结点, 也可以是另一个二元表达式结点
// 此时Child的表达式优先级更高