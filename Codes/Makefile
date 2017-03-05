# Genet Martin : Projet de SDA2
#
# Compile tous les programmes de tests.
#

CFLAGS = -Wall -g

TESTS = test_gen test_union test_inter
TESTSTRIE = test_gen_trie test_union_trie test_inter_trie
TESTSAPP = test_app test_compo

all : $(TESTS) $(TESTSTRIE) $(TESTSAPP)


# Tests sur les ensembles non triés

test_gen : test_gen.o ensemble.o
	gcc -o $@ $^ $(CFLAGS)
	
test_union : test_union.o ensemble.o
	gcc -o $@ $^ $(CFLAGS)

test_inter : test_inter.o ensemble.o
	gcc -o $@ $^ $(CFLAGS)


test_gen.o : test_gen.c 
	gcc -c $< $(CFLAGS)
	
test_union.o : test_union.c
	gcc -c $< $(CFLAGS)

test_inter.o : test_inter.c
	gcc -c $< $(CFLAGS)

ensemble.o : ensemble.c ensemble.h
	gcc -c $< $(CFLAGS)


# Tests sur les ensembles triés

test_gen_trie : test_gen_trie.o ensembletrie.o
	gcc -o $@ $^ $(CFLAGS)
	
test_union_trie : test_union_trie.o ensembletrie.o
	gcc -o $@ $^ $(CFLAGS)

test_inter_trie : test_inter_trie.o ensembletrie.o
	gcc -o $@ $^ $(CFLAGS)


test_gen_trie.o : test_gen_trie.c 
	gcc -c $< $(CFLAGS)
	
test_union_trie.o : test_union_trie.c
	gcc -c $< $(CFLAGS)

test_inter_trie.o : test_inter_trie.c
	gcc -c $< $(CFLAGS)

ensembletrie.o : ensembletrie.c ensembletrie.h
	gcc -c $< $(CFLAGS)


# Tests sur les application

test_app : test_app.o application.o liste.o ensembletrie.o
	gcc -o $@ $^ $(CFLAGS)

test_compo : test_compo.o application.o liste.o ensembletrie.o
	gcc -o $@ $^ $(CFLAGS)

application.o : application.c application.h liste.h
	gcc -c $< $(CFLAGS)

liste.o : liste.c liste.h ensembletrie.h
	gcc -c $< $(CFLAGS)

test_app.o : test_app.c ensembletrie.h application.h liste.h
	gcc -c $< $(CFLAGS)

test_compo.o : test_compo.c ensembletrie.h application.h liste.h
	gcc -c $< $(CFLAGS)


# Cibles utilitaires

clean :
	rm *.o $(TESTS) $(TESTSTRIE) $(TESTSAPP)

