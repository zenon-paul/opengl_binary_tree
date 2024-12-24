#include"binary_tree.h"
#define N_MAX 9
float all_avg;
float all_sigma;
float avl_avg;
float avl_sigma;
float cmp_avg;
float cmp_sigma;
int all_tree_num;
int avl_tree_num;
int cmp_tree_num;

void print_hight_analysis(int tree_num, float avg, float sigma, const char* tree_name) {
	printf(">>Analysis of hight of %s<<\n",tree_name);
	printf("    Number of trees  : %d\n",tree_num);
	printf("    Average of hight : %f\n",avg);
	printf("    Variance of hight: %f\n",sigma);
}

void analyze_all_tree_hight(Tree* trees) {
	float hight_sum = 0.0;
	float hight2_sum = 0.0;
	float sigma = 0.0;
	int tree_num = 0;

	for (; trees[tree_num] != NULL; tree_num++) {
		int h = calculate_hight(trees[tree_num]) - 1;
		hight_sum += (float)h;
		hight2_sum += (float)(h * h);
	}

	hight_sum /= tree_num;
	hight2_sum /= tree_num;
	sigma = hight2_sum - hight_sum * hight_sum;
	print_hight_analysis(tree_num,hight_sum,sigma,"all distinct trees");

	all_avg = hight_sum;
	all_sigma = sigma;
	all_tree_num = tree_num;
}

void analyze_AVL_tree_hight(Tree* trees) {
	float hight_sum = 0.0;
	float hight2_sum = 0.0;
	float sigma = 0.0;
	int tree_num = 0;

	int i = 0;
	for (i = 0; trees[i] != NULL; i++) {
		if (is_AVL_tree(trees[i])) {
			int h = calculate_hight(trees[i]) - 1;
			//printf("%d\n",h);
			hight_sum += (float)h;
			hight2_sum += (float)(h * h);
			tree_num++;
		}
	}

	hight_sum /= tree_num;
	hight2_sum /= tree_num;
	sigma = hight2_sum - hight_sum * hight_sum;
	print_hight_analysis(tree_num,hight_sum,sigma,"distinct AVL trees");
	avl_avg = hight_sum;
	avl_sigma = sigma;
	avl_tree_num = tree_num;
}

void analyze_complete_binary_tree_hight(Tree* trees) {
	float hight_sum = 0.0;
	float hight2_sum = 0.0;
	float sigma = 0.0;
	int tree_num = 0;

	int i = 0;
	for (i = 0; trees[i] != NULL; i++) {
		if (is_complete_binary_tree(trees[i])) {
			int h = calculate_hight(trees[i]) - 1;
			//printf("%d\n", h);
			hight_sum += (float)h;
			hight2_sum += (float)(h * h);
			tree_num++;
		}
	}

	hight_sum /= tree_num;
	hight2_sum /= tree_num;
	sigma = hight2_sum - hight_sum * hight_sum;
	print_hight_analysis(tree_num,hight_sum,sigma,"distinct complete binary trees");
	cmp_avg = hight_sum;
	cmp_sigma = sigma;
	cmp_tree_num = tree_num;
}

void analyze_all_hight_distribution(int histogram[][N_MAX], Tree* trees,int n) {
	for (int i = 0; trees[i] != NULL; i++) histogram[n][calculate_hight(trees[i])-1]++;
}

void analyze_avl_hight_distribution(int histogram[][N_MAX], Tree* trees, int n) {
	for (int i = 0; trees[i] != NULL; i++) if(is_AVL_tree(trees[i])) histogram[n][calculate_hight(trees[i]) - 1]++;
}

void analyze_cmp_hight_distribution(int histogram[][N_MAX], Tree* trees, int n) {
	for (int i = 0; trees[i] != NULL; i++) if(is_complete_binary_tree(trees[i])) histogram[n][calculate_hight(trees[i]) - 1]++;
}

void report_trees(const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "w");
	if (fp == NULL) {
		return;
	}

	int all_histogram[N_MAX + 1][N_MAX];
	int avl_histogram[N_MAX + 1][N_MAX];
	int cmp_histogram[N_MAX + 1][N_MAX];

	for (int i = 0; i < N_MAX + 1; i++) for (int j = 0; j < N_MAX; j++) {
		all_histogram[i][j] = 0;
		avl_histogram[i][j] = 0;
		cmp_histogram[i][j] = 0;
	}

	for (int i = 1; i <= N_MAX; i++) {
		Tree* trees = get_different_trees(i);

		analyze_all_tree_hight(trees);
		analyze_AVL_tree_hight(trees);
		analyze_complete_binary_tree_hight(trees);
		analyze_all_hight_distribution(all_histogram, trees, i);
		analyze_avl_hight_distribution(avl_histogram, trees, i);
		analyze_cmp_hight_distribution(cmp_histogram, trees, i);
		
		fprintf(fp,"%d,%f,%f,%f,%f,%f,%f,%d,%d,%d,\n",i,all_avg,all_sigma,avl_avg,avl_sigma,cmp_avg,cmp_sigma,all_tree_num,avl_tree_num,cmp_tree_num);

		for (int i = 0; trees[i] != NULL; i++) delete_tree(trees[i]);
		free(trees);
	}
	
	for (int i = 0; i < N_MAX; i++) {
		for (int j = 1; j < N_MAX + 1; j++) {
			all_histogram[0][i] += all_histogram[j][i];
			avl_histogram[0][i] += avl_histogram[j][i];
			cmp_histogram[0][i] += cmp_histogram[j][i];
		}
	}

	for (int i = 0; i < N_MAX+1; i++) {
		fprintf(fp,"%d,",i);
		for (int j = 0; j < N_MAX; j++) {
			fprintf(fp,"%d,",all_histogram[i][j]);
		}
		fprintf(fp, "\n");
	}

	for (int i = 0; i < N_MAX + 1; i++) {
		fprintf(fp, "%d,", i);
		for (int j = 0; j < N_MAX; j++) {
			fprintf(fp, "%d,", avl_histogram[i][j]);
		}
		fprintf(fp, "\n");
	}

	for (int i = 0; i < N_MAX + 1; i++) {
		fprintf(fp, "%d,", i);
		for (int j = 0; j < N_MAX; j++) {
			fprintf(fp, "%d,", cmp_histogram[i][j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
}