# Series Management Project

## Overview

The **Series Management Project** is a C++ application designed to manage movies and series, enabling administrators to perform CRUD operations and clients to search, filter, and interact with media content effectively. This project is implemented using custom data structures like compressed tries, splay trees, and hash tables, focusing on efficient data storage and retrieval.

---

## Features

### Admin Features

- **Add Media**: Add new movies or series, specifying details like name, genre, language, and more.
- **Delete Media**: Delete existing movies or series. Media names in compressed tries are set to empty strings without removing nodes.
- **Update Media**: Modify details of existing movies or series.

### Client Features

- **Simple Search**: Search for media using prefixes via a compressed trie.
- **Advanced Search**:
  - Uses splay trees, compressed tries, and Levenshtein distance to find and suggest relevant media.
  - Filters results where media names are non-empty.
- **View Details**: Display full details of selected movies or series.
- **Filter Media**: Filter movies or series based on genre, language, or country of origin using a hash table.
- **Recommendations**: Generate recommendations based on hash tables and splay trees.
- **Favorites Management**: Add or remove media from a personal favorites list.

---

## Data Structures Used

### 1. Compressed Trie

- **Purpose**: Efficient prefix-based searching for media names.
- **Key Operation**: Media names marked as empty strings (`""`) on deletion, ensuring nodes remain intact.

### 2. Splay Tree

- **Purpose**: Self-adjusting binary search tree for advanced search and frequent access optimization.
- **Key Operation**: Recently accessed media is splayed to the root for faster subsequent searches.

### 3. Hash Table

- **Purpose**: Categorize and retrieve media efficiently based on genre, language, and country.
- **Key Operation**: Supports filtering and recommendation functionality.

---



## Advanced Search Workflow

1. **Prefix Search**: Compressed trie retrieves media names starting with the given prefix.
2. **Splay Integration**: Results are checked in the splay tree for frequency optimization.
3. **Levenshtein Distance**: Suggestions for similar media names (distance ≤ 2) are generated if no exact matches are found.
4. **Final Output**: Sorted suggestions are displayed to the client.

---





