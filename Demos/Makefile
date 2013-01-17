CC=gcc
CFLAGS=-I.
#DEPS = Stack/stack_stat.h

#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

ss: ss_test.o ../Stack/stack_stat.o 
	gcc -o ss_test ss_test.o ../Stack/stack_stat.o -I.

ds: ds_test.o ../Stack/stack_dyn.o
	gcc -o ds_test ds_test.o ../Stack/stack_dyn.o -I.

sq: sq_test.o ../Queue/queue_stat.o
	gcc -o sq_test sq_test.o ../Queue/queue_stat.o -I.

dq: dq_test.o ../Queue/queue_dyn.o
	gcc -o dq_test dq_test.o ../Queue/queue_dyn.o -I.

mh: mh_test.o ../Heap/minheap.o
	gcc -o mh_test mh_test.o ../Heap/minheap.o -I.

bt: bt_test.o ../Btree/btree.o
	gcc -o bt_test bt_test.o ../Btree/btree.o -I.

at: at_test.o ../AVL/avl.o
	gcc -o at_test at_test.o ../AVL/avl.o -I.

hoa: hoa_test.o ../HashTable/open_addressing.o
	gcc -o hoa_test hoa_test.o ../HashTable/open_addressing.o -I.

hca: hca_test.o ../HashTable/closed_addressing.o
	gcc -o hca_test hca_test.o ../HashTable/closed_addressing.o -I.

gr: gr_test.o ../Graph/adj_list.o ../Graph/adj_matrix.o ../Graph/adj_vector.o ../Queue/queue_stat.o
	gcc -o gr_test gr_test.o ../Graph/adj_list.o ../Graph/adj_matrix.o ../Graph/adj_vector.o ../Queue/queue_stat.o -I.

clean:
	rm -rvf *.o ../Queue/*.o ../Stack/*.o ../Heap/*.o ../Btree/*.o ../AVL/*.o ../HashTable/*.o ../Graph/*.o tree.* ss_test ds_test sq_test dq_test mh_test bt_test at_test hoa_test hca_test gr_test