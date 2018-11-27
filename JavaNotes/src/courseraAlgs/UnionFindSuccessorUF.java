/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package courseraAlgs;

/**
 *  Successor with delete. 
 * Given a set of n integers S={0,1,...,n−1} 
 * and a sequence of requests of the following form:

    Remove x from S
    Find the successor of x: the smallest y in S such that y≥xy \ge y ≥ x.

design a data type so that all operations (except construction) take logarithmic time or better in the worst case.
 * @author default
 */
public class UnionFindSuccessorUF {
    private int[] parent;
    private int[] size;
    private int[] large;
    private int count;

    public UnionFindSuccessorUF(int n) {
        count = n;
        parent = new int[n];
        size = new int[n];
        large = new int[n];
        for(int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = i;
            large[i] = i;
        }
    }
 
    public int count() {
        return count;
    }
    
    private void validate(int p) {
        int n = parent.length;
        if(n < 0 || p >= n) {
            throw new IllegalArgumentException("Index out of range");
        }
    }
    
    public int find(int p) {
        return large[root(p)];
    }
    
    public int root(int p) {
        validate(p);
        while(p != parent[p]) {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;
    }
    public boolean connected(int p, int q) {
        return root(p) == root(q);
    }
    
    public void union(int p, int q) {
        int rootP = parent[p];
        int rootQ = parent[q];
        
        if(rootP == rootQ) {
            return;
        }
        int largeP = large[rootP];
        int largeQ = large[rootQ];
        
        // make smaller root point to larger one
        if(size[rootP] < size[rootQ]) {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
            if(largeP > largeQ) {
                large[rootQ] = largeP;  
            }
        }
        else {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
            if(largeQ > largeP) {
                large[rootP] = largeQ;  
            }
        }
        count--;
    }
}
