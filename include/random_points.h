#ifndef RANDOM_POINTS_H
#define RANDOM_POINTS_H

#include <vector>
#include <utility>
#include "block_info.h"
#include "cxxopts.hpp"

// Function to generate random 2D points
std::vector<PointMetadata> generateRandomPoints(int numPointsPerProcess, const Opts& opts);

// Function to partition points and communicate them to the appropriate processors
void partitionPoints(const std::vector<PointMetadata>& localPoints, std::vector<PointMetadata>& localPoints_out_partitioned, const Opts& opts);

// Function to perform finer partitioning within each processor
void finerPartition(const std::vector<PointMetadata>& points, int numBlocksPerProcess, std::vector<std::vector<PointMetadata>>& finerPartitions, const Opts& opts, bool is_test);

// Function to calculate centers of gravity for each block
std::vector<std::vector<double>> calculateCentersOfGravity(const std::vector<std::vector<PointMetadata>> &finerPartitions, const Opts& opts);

// Function to send centers of gravity to processor 0
void AllGatherCenters(const std::vector<std::vector<double>>& centers, std::vector<std::pair<std::vector<double>, int>>& allCenters, const Opts& opts);

// Function to randomly reorder centers at processor 0
void reorderCenters(std::vector<std::vector<double>>& centers, std::vector<std::pair<std::vector<double>, int>>& allCenters, std::vector<int>& permutation, std::vector<int>& localPermutation, const Opts& opts);

// Function to broadcast reordered centers to all processors
void broadcastCenters(std::vector<std::pair<std::vector<double>, int>>& allCenters, int numCenters, const Opts& opts);

// Function to perform k-means++ clustering with iterations and parallelization
std::vector<int> kMeansPlusPlus(const std::vector<PointMetadata>& metadata, int k, int dim, int maxIterations, int rank, int seed);

// Function to read points from CSV files
std::vector<PointMetadata> readPointsConcurrently(const std::string& filename, int numBlocks, const Opts& opts);

// Function to perform random clustering
std::vector<int> randomClustering(const std::vector<PointMetadata>& metadata, int k, int dim, int seed, bool is_test);

// Function to partition points directly
void partitionPointsDirectly(
    const std::vector<PointMetadata>& localPoints, 
    std::vector<std::vector<PointMetadata>>& finerPartitions, 
    int numBlocks,
    const Opts& opts);

#endif // RANDOM_POINTS_H