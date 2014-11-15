#pragma once

#include "gist/entry.h"
#include "gist/node.h"
#include "leaf_entry.h"
#include <vector>

template <typename P>
class InnerEntry : public Entry<P> {
private:
    Node<P> node;
    InnerEntry<P>* parent;

public:
    InnerEntry<P> () {
        node = *(new Node<P>(std::vector<Entry<P> *>()));
        this->predicate = *(new P());
        parent = nullptr;
    }

    InnerEntry<P> (std::vector<Entry<P> *> entries) {
        node = *(new Node<P>(entries));
        this->predicate = *(new P(getSubpredicates()));
    }

	InnerEntry<P>* getParent() {
		return parent;
	}

    std::vector<Entry<P> *> getChildren() {
        return node.getEntries();
    }

	std::vector<P*> getSubpredicates() {
		std::vector<Entry<P> *> children = getChildren();
		std::vector<P*> result;
		for (typename std::vector<Entry<P> *>::iterator child = children.begin(); child != children.end(); ++child) {
			result.push_back((*child) -> getPredicate());
		}	
		return result;
	}

    void setChildren (std::vector<Entry<P> *> entries) {
        node.setEntries(entries);
    }

    void insert(const Entry<P> &E) {
        E.setParent(this);
        node.insert(E);
    }

    void setParent(InnerEntry<P>* E) {
        parent = E;
    }
};