/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package courseraAlgs;

/**
 *
 * @author default
 */
public class WightenedQuickUnionUF {
    private int[] parent;
    private int[] size;
    private int count;

    public WightenedQuickUnionUF(int n) {
        count = n;
        parent = new int[n];
        size = new int[n];
        for(int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = i;
        }
    }
    
    public int count() {
        return count;
    }
    
    private void validate(int p) {
        int n = parent.length;
        if(p < 0 || p >= n) {
            throw new IllegalArgumentException("Index: " + p + " is not in a range of 0 and " + (n - 1));
        }
    }
    
    public int find(int p) {
        validate(p);
        while(p != parent[p]) {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;
    }
    
    public boolean connected(int p, int q) {
        return find(p) == find(q);
    }
    
    public void union(int p, int q) {
        int rootP = parent[p];
        int rootQ = parent[q];
        
        if(rootP == rootQ) {
            return;
        }
        
        // make smaller root point to larger one
        if(size[rootP] < size[rootQ]) {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
        }
        else {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
        count--;
    }
}
