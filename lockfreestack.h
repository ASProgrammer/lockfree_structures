#ifndef LOCKFREESTACK_H
#define LOCKFREESTACK_H

#include <atomic>
#include <memory>

namespace lockfree {

template <typename T>
class LockfreeStack {
    struct Node {
        std::shared_ptr<T> m_data;
        Node* m_next;

        Node(const T& value):
            m_data { std::make_shared<T>(value) },
            m_next { nullptr }
        { }
    };

public:
    LockfreeStack():
        m_head { nullptr }
    { }

    void push(const T& new_value);
    std::shared_ptr<T> pop();

private:
    std::atomic<Node*> m_head;
};

template <typename T>
void LockfreeStack<T>::push(const T& new_value)
{
    auto new_head = new Node { new_value };
    new_head->m_next = m_head.load();
    while (!m_head.compare_exchange_weak(new_head->m_next, new_head));
}

template <typename T>
std::shared_ptr<T> LockfreeStack<T>::pop()
{
    Node* old_head = m_head.load();
    while (old_head && !m_head.compare_exchange_weak(old_head, old_head->m_next));
    return old_head ? old_head->m_data : nullptr;
}

}

#endif // LOCKFREESTACK_H
