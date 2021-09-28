#include <iostream>
#include <bits/stdc++.h>

class ITodoComponent
{
    public:
        virtual std::string getTodoText() = 0;
};

class TodoLeaf: public ITodoComponent
{
    public:
        TodoLeaf(std::string todo_text)
        {
            m_todo_text = todo_text;
        };
        std::string getTodoText() 
        {
            return m_todo_text;
        };
    private:
        std::string m_todo_text;
};

class TodoComposite: public ITodoComponent
{
    public:
        void addTodoComponent(ITodoComponent *component)
        {
            m_todo_list.push_back(component);
        };
        
        std::string getTodoText()
        {   
            std::string todo_text = "";
            for(int i = 0; i < m_todo_list.size(); i++)
            {   
                todo_text += m_todo_list[i]->getTodoText() + " ";
            }

            return todo_text;
        };
    private:
        std::vector<ITodoComponent*> m_todo_list;
};

int main () 
{
    TodoComposite *todoList1 = new TodoComposite();
    todoList1->addTodoComponent(new TodoLeaf("My banana job 1"));
    todoList1->addTodoComponent(new TodoLeaf("My banana job 2"));
    todoList1->addTodoComponent(new TodoLeaf("My banana job 3"));

    TodoComposite *todoList2 = new TodoComposite();
    todoList2->addTodoComponent(todoList1);
    todoList2->addTodoComponent(new TodoLeaf("My apple job 1"));

    std::cout << todoList2->getTodoText() << std::endl;
    return 0;
}