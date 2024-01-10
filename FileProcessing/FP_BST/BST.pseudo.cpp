insertBST(T, newKey)
  p <- T;
  q <- null;
  stack <- [];

  // find position to insert newKey while storing parent node on stack
  while (p != null) do
    if (newKey = p.key) then return; // newKey already exists in T
    end if

    q <- p;
    push q on stack;
    
    if (newKey < p.key) then p <- p.left;
    else then p <- p.right;
    end if
  end while

  // create new node
  newNode <- getBSTNode();
  newNode.key <- newKey;

  // insert newNode as a child of q
  if (T = null) then T <- newNode;
  else if (newKey < q.key) then q.left <- newNode;
  else then q.right <- newNode;
  end if

  // update height while popping parent node from stack
  while (stack is not empty) do
    q <- pop from stack;
    q.height <- 1 + max(q.left.height, q.right.height);
  end while
end insertBST

//~~~~~~~~~~~~~~~~~~~~~~

deleteBST(T, deleteKey)
  p <- T;
  q <- null;
  stack <- [];

  // find position of deleteKey while storing parent node on stack
  while (p != null and deleteKey != p.key) do
    q <- p;
    push q on stack;

    if (deleteKey < p.key) then p <- p.left;
    else then p <- p.right;
    end if
  end while

  if (p = null) then return;  // deleteKey was not found
  end if
~~~~~~~~~~~~~~~~~~~~~~~
  if (p.left != null and p.right != null) then  // case of degree 2 is reduced to case of degree 0 or case of degree 1
    push p on stack;
    tempNode <- p;

    if (p.left.height <= p.right.height) then
      p <- p.right;
      while (p.left != null)
        push p on stack;
        p <- p.left;
      end while
    else then
      p <- p.left;
      while (p.right != null)
        push p on stack;
        p <- p.right;
      end while
    end if

    tempNode.key <- p.key;
    q <- top of stack;
  end if
  ~~~~~~~~~~~~~~~~~~~~~~

  // now degree of p is 0 or 1
  // delete p from T
  if (p.left = null and p.right = null) then  // case of degree 0
    if (q = null) then T <- null; // case of root
    
    else if (q.left = p) then q.left = null;
    else then q.right = null;
    end if
  else then // case of degree 1
    if (p.left != null) then
      if (q = null) then T <- T.left; // case of root
      else if (q.left = p) then q.left <- p.left;
      else then q.right <- p.left;
      end if
    else then
      if (q = null) then  T <- T.right; // case of root
      else if (q.left = p) then q.left <- p.right;
      else then q.right <- p.right;
      end if
    end if
  end if

  delete p;

  // update height while popping parent node from stack
  while (stack is not empty) do
    q <- pop from stack;
    q.height <- 1 + max(q.left.height, q.right.height);
  end while
end deleteBST