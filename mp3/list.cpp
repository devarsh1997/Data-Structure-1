/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    clear();/// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
    length = 0;
    ListNode *temp;
    while(head!=NULL){
        temp = head->next;
        delete head;
        head = temp;
    }
    head = NULL;
    tail = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1

    if(head != NULL)
    {
        ListNode* newnode = new ListNode(ndata);
        newnode->next = head;
        head->prev = newnode;
        length = length + 1;
        head = newnode;
    }
    else
    {
        ListNode* newnode = new ListNode(ndata);
        length = length + 1;
        head = newnode;
        tail = newnode;
    }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
    if(tail != NULL)
    {
        ListNode* newnode = new ListNode(ndata);
        newnode->prev = tail;
        tail->next = newnode;
        length = length + 1;
        tail = newnode;
    }
    else
    {
         ListNode* newnode = new ListNode(ndata);
         length = length + 1;
         head = newnode;
         tail = newnode;
    }


}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    
    if(startPoint == NULL){
		return;
	}
	if(startPoint == endPoint)
	{
	    return;
	}

	ListNode* temp2 = endPoint->next; ///////////////mark endPoint->next
	ListNode* temp3 = startPoint->prev; //////////////mark startPoint->prev


	ListNode* start = startPoint;
	ListNode* end = endPoint;

    ListNode* temp = temp3;
	ListNode* curr = startPoint;
	
	while(curr != endPoint)
	{
	    temp = curr->prev;
	    curr->prev = curr->next;
	    curr->next = temp;
	    curr = curr->prev;
	}
	temp = curr->prev;
	curr->prev = temp3;
	curr->next = temp;
	
	startPoint = end;
	endPoint = start;
	start->next = temp2;
	

	//////check head tail
	if(temp3 == NULL)
	{
	    head = startPoint;
	}
	else
	{
	    temp3->next = startPoint;
	}
	    
	if(temp2 == NULL)
	{
	    tail = endPoint;
	}
	else
	{
	    temp2->prev = endPoint;
	}
	    
	
}







/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{

    if( head == NULL)
    {
        return;
    }
    if( n == 0 || n == 1 || n < 0)
    {
        return;
    }

    if( head == NULL)
    {
        return;
    }
    if( n == 0 || n == 1 || n < 0)
    {
        return;
    }

    ListNode* temp = head;
    ListNode* first = temp;
    while(temp != tail){

        int n2 = n;
        for(int i = 1; i < n;i++){

            temp = temp->next;
            if( temp == tail)
            {
                reverse(first, temp);
                return;
            }
        }
        reverse(first, temp);

        first = temp->next;
        temp = first;
    }


}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
    if(head == NULL || head->next == NULL)
    {
        return;
    }
    ListNode* curr = head;
    while(curr->next->next != NULL)
    {
        tail->next = curr->next;
        curr->next->next->prev = curr;
        curr->next->prev = tail;
        curr->next = curr->next->next;

        tail = tail->next;
        tail->next = NULL;
        curr = curr->next;

    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    if(splitPoint < 0)
        return NULL;
    if( splitPoint == 0)
        return start;

    ListNode* count = start;
    int c = 0;
    while(count != NULL)
    {
        count = count->next;
        c++;
    }
    if(splitPoint > c || splitPoint == c)
    {
        return NULL;
    }

    ListNode* temp = start;
    for (int i = 0; i < splitPoint; i++)
    {
        temp = temp->next;
    }
    ListNode* t1 = temp->prev;
    t1->next = NULL;
    temp->prev = NULL;


    return temp; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    if(first == NULL)
        return second;
    if(second == NULL)
        return first;

    ListNode* result;
    if(first->data < second->data)
    {
        result = first;
        first = first->next;
    }
    else
    {
        result = second;
        second = second->next;
    }
    ListNode* temp = result;
    while(first != NULL && second != NULL)
    {
        if(first->data < second->data)
        {
            temp->next = first;
            first->prev = temp;
            first = first->next;
            temp = temp->next;
        }
        else
        {
            temp->next = second;
            second->prev = temp;
            second = second->next;
            temp = temp->next;
        }
    }// end of while

    if(first != NULL)
    {
        temp->next = first;
        first->prev = temp;
    }
    if(second != NULL)
    {
        temp->next = second;
        second->prev = temp;
    }
    /// @todo Graded in MP3.2
    return result; // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    if(chainLength == 1)
        return start;
    int middle = chainLength / 2;
    ListNode* second = split(start, middle);
    ListNode* t1 = mergesort(start, middle);
    ListNode* t2 = mergesort(second, chainLength - middle);
    ListNode* result = merge(t1, t2);
    return result; // change me!
}
