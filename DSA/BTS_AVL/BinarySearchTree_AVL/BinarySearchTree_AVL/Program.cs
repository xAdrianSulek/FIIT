using System;


namespace TryingShit
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            AVLTree avlTree = new AVLTree();
            Random random = new Random();
            
            /*
            avlTree.add(10);
            avlTree.add(15);
            avlTree.add(20);
            avlTree.add(25);
            avlTree.delete(20);
            avlTree.display();
            */
            for (int i = 0; i < 10; i++)
            {
                avlTree.add(random.Next());
            }
            avlTree.display();
        }
    }

    
    class AVLTree
    {

        public const int NUMBER = 0;
        Node parent;
        Node randomNode;

        internal class Node
        {
            public int height;
            public int data;
            public Node left;
            public Node right;

            
            public Node()
            {
            }
            public Node(int data)
            {
                this.data = data;
                height = 0;
            }
        }

        public void add(int data)
        {
            Node newNode = new Node(data);
            if (parent != null)
            {
                parent = insert(parent, newNode, data);
            }
            else
            {
                parent = newNode;
            }
        }
        
        
        public Node insert(Node currentNode, Node newNode, int data)
        {
            if (currentNode == null)
            {
                currentNode = newNode;
                return currentNode;
            }
            else if (data < currentNode.data)
            {
                currentNode.left = insert(currentNode.left, newNode, data);
                currentNode = balance(currentNode);
            }
            else if (data > currentNode.data)
            {
                currentNode.right = insert(currentNode.right, newNode, data);
                currentNode = balance(currentNode);
            }
            
            return currentNode;
        }
        
        public Node balance(Node node)
        {
            int difference = HeightFromLeft(node) - HeigtFromRight(node);
            if (difference > 1)
            {
                if (HeightFromLeft(node.left) - HeigtFromRight(node.left) > 0)
                {
                    node = rotationLeftLeft(node);
                }
                else
                {
                    node = rotationLeftRight(node);
                }
            }
            
            else if (difference < -1)
            {
                if (HeightFromLeft(node.right) - HeigtFromRight(node.right) > 0)
                {
                    node = rotationRightLeft(node);
                }
                else
                {
                    node = rotationRightRight(node);
                }
            }

            return node;
        }

        public void Find(int data)
        {
            if (FindFromTree(parent, data) == data)
            {
                Console.WriteLine("Node was found: " + data);
            }
            else
            {
                Console.WriteLine("Node was not found");
            }
        }
        public int FindFromTree(Node node, int data)
        {
            if (data == node.data)
            {
                return data;
            }
            else
            {
                if (data < node.data)
                {
                    return FindFromTree(node.left, data);
                }
                else
                {
                    return FindFromTree(node.right, data);
                }
            }
        }

        public void delete(int data)
        {
            parent = deleteFromTree(parent, data);
        }

        public Node deleteFromTree(Node node, int data)
        {
            if (node == null)
            {
                return null;
            }
            else
            {
                if (data < node.data)
                {
                    node.left = deleteFromTree(node.left, data);
                    if (HeightFromLeft(node) - HeigtFromRight(node) == -2)
                    {
                        if (HeightFromLeft(node.right) - HeigtFromRight(node.right) <= 0)
                        {
                            node = rotationRightRight(node);
                        }
                        else
                        {
                            node = rotationRightLeft(node);
                        }
                    }
                }
                else if (data > node.data)
                {
                    node.right = deleteFromTree(node.right, data);
                    if (HeightFromLeft(node) - HeightFromLeft(node) == 2)
                    {
                        if (HeightFromLeft(node.left) - HeigtFromRight(node.right) >= 0)
                        {
                            node = rotationLeftLeft(node);
                        }
                        else
                        {
                            node = rotationLeftRight(node);
                        }
                    }
                }
                else
                {
                    if (node.right != null)
                    {
                        randomNode = node.right;
                        while (randomNode.left != null)
                        {
                            randomNode = randomNode.left;
                        }

                        node.data = randomNode.data;
                        node.right = deleteFromTree(node.right, randomNode.data);
                        if (HeightFromLeft(node) - HeigtFromRight(node) == 2)
                        {
                            if (HeightFromLeft(node.left) - HeigtFromRight(node.left) >= 0)
                            {
                                node = rotationLeftRight(node);
                            }
                            else
                            {
                                node = rotationLeftRight(node);
                            }
                        }
                    }

                    else
                    {
                        return node.left;
                    }
                }
            }

            return node;
        }
        
        
        public int HeightFromLeft(Node node)
        {
            int vyska = 0;
            if (node!= null)
            {
                vyska = HeightFromLeft(node.left) + 1;
            }

            return vyska;
        }
        
        public int HeigtFromRight(Node node)
        {
            int vyska = 0;
            if (node!= null)
            {
                vyska = HeigtFromRight(node.right) + 1;
            }

            return vyska;
        }
        


        public int HeightHelper(Node node)
        {
            if (node != null)
            {
                return node.height;
            }
            return 0;
        }

        
        /// 
        /// Mozno bude lepsie storovat height v kazdom note. tato rekurzia moze trvat dlho
        ///
        

        public void display()
        {
            if (parent == null)
            {
                Console.WriteLine("Strom je prazdny");
            }
            else
            {
                displayFromLevels(parent);
            }
        }

        public void displayFromLevels(Node node)
        {
            if (node != null)
            {
                Console.Write(node.data + " ");

                if (node.left != null)
                {
                    Console.Write("L:");
                    displayFromLevels(node.left);
                }

                if (node.right != null)
                {
                    Console.Write("R:");
                    displayFromLevels(node.right);
                }
            }
        }

        public Node rotationRightRight(Node parentOfTriangle)
        {
            Node rotation = parentOfTriangle.right;
            parentOfTriangle.right = rotation.left;
            rotation.left = parentOfTriangle;
            return rotation;
        }
        
        public Node rotationRightLeft(Node parentOfTriangle)
        {
            Node rotation = parentOfTriangle.right;
            parentOfTriangle.right = rotationLeftLeft(rotation);
            return rotationRightRight(parentOfTriangle);
        }
        
        public Node rotationLeftLeft(Node parentOfTriangle)
        {
            Node rotation = parentOfTriangle.left;
            parentOfTriangle.left = rotation.right;
            rotation.right = parentOfTriangle;
            return rotation;
        }
        
        public Node rotationLeftRight(Node parentOfTriangle)
        {
            Node rotation = parentOfTriangle.left;
            parentOfTriangle.left = rotationRightRight(rotation);
            return rotationLeftLeft(parentOfTriangle);
        }
        
    }
}