document.addEventListener('DOMContentLoaded', () => {
    const recipesList = document.getElementById('recipesList');
    const modal = document.getElementById('recipeModal');
    const addRecipeBtn = document.getElementById('addRecipeBtn');
    const closeBtn = document.querySelector('.close');
    const recipeForm = document.getElementById('recipeForm');
    
    let editingRecipeId = null;
    let currentPage = 1;
    const itemsPerPage = 3;
    let allRecipes = [];
    let currentSort = 'asc';

    function loadRecipes() {
        fetch('/api/recipes')
            .then(response => response.json())
            .then(recipes => {
                allRecipes = recipes;
                displayRecipes();
            })
            .catch(error => console.error('Ошибка:', error));
    }

    function displayRecipes() {
        const searchTerm = document.getElementById('searchInput').value.toLowerCase();
        let filteredRecipes = allRecipes.filter(recipe => 
            recipe.title.toLowerCase().includes(searchTerm)
        );

        filteredRecipes.sort((a, b) => {
            if (currentSort === 'asc') {
                return a.title.localeCompare(b.title);
            } else {
                return b.title.localeCompare(a.title);
            }
        });

        const startIndex = (currentPage - 1) * itemsPerPage;
        const endIndex = startIndex + itemsPerPage;
        const paginatedRecipes = filteredRecipes.slice(startIndex, endIndex);

        recipesList.innerHTML = paginatedRecipes.map(recipe => `
            <div class="recipe-card" data-id="${recipe.id}">
                <div class="recipe-header">
                    <h2>${recipe.title}</h2>
                    <div class="recipe-actions">
                        <button class="edit-btn" onclick="editRecipe(${recipe.id})">✎</button>
                        <button class="delete-btn" onclick="deleteRecipe(${recipe.id})">✖</button>
                    </div>
                </div>
                <p><strong>Ингредиенты:</strong> ${recipe.ingredients.join(', ')}</p>
                <p><strong>Инструкция:</strong> ${recipe.instructions}</p>
                <p><strong>Время приготовления:</strong> ${recipe.cookingTime}</p>
            </div>
        `).join('');

        const totalPages = Math.ceil(filteredRecipes.length / itemsPerPage);
        const paginationContainer = document.getElementById('pagination');
        paginationContainer.innerHTML = `
            <button onclick="changePage(1)" ${currentPage === 1 ? 'disabled' : ''}>«</button>
            <button onclick="changePage(${currentPage - 1})" ${currentPage === 1 ? 'disabled' : ''}>‹</button>
            <span>Страница ${currentPage} из ${totalPages}</span>
            <button onclick="changePage(${currentPage + 1})" ${currentPage === totalPages ? 'disabled' : ''}>›</button>
            <button onclick="changePage(${totalPages})" ${currentPage === totalPages ? 'disabled' : ''}>»</button>
        `;
    }

    window.changePage = (page) => {
        currentPage = page;
        displayRecipes();
    };

    window.toggleSort = () => {
        currentSort = currentSort === 'asc' ? 'desc' : 'asc';
        displayRecipes();
    };

    addRecipeBtn.onclick = () => {
        editingRecipeId = null;
        recipeForm.reset();
        modal.style.display = 'block';
    };

    closeBtn.onclick = () => {
        modal.style.display = 'none';
    };

    window.onclick = (event) => {
        if (event.target === modal) {
            modal.style.display = 'none';
        }
    };

    window.editRecipe = (id) => {
        editingRecipeId = id;
        fetch(`/api/recipes/${id}`)
            .then(response => response.json())
            .then(recipe => {
                document.getElementById('title').value = recipe.title;
                document.getElementById('ingredients').value = recipe.ingredients.join(', ');
                document.getElementById('instructions').value = recipe.instructions;
                document.getElementById('cookingTime').value = recipe.cookingTime;
                modal.style.display = 'block';
            })
            .catch(error => console.error('Ошибка:', error));
    };

    window.deleteRecipe = (id) => {
        if (confirm('Вы уверены, что хотите удалить этот рецепт?')) {
            fetch(`/api/recipes/${id}`, {
                method: 'DELETE'
            })
            .then(response => {
                if (response.ok) {
                    loadRecipes();
                }
            })
            .catch(error => console.error('Ошибка:', error));
        }
    };

    recipeForm.onsubmit = (e) => {
        e.preventDefault();
        
        const recipeData = {
            title: document.getElementById('title').value,
            ingredients: document.getElementById('ingredients').value.split(',').map(i => i.trim()),
            instructions: document.getElementById('instructions').value,
            cookingTime: document.getElementById('cookingTime').value
        };

        const method = editingRecipeId ? 'PUT' : 'POST';
        const url = editingRecipeId ? `/api/recipes/${editingRecipeId}` : '/api/recipes';

        fetch(url, {
            method: method,
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(recipeData)
        })
        .then(response => response.json())
        .then(() => {
            loadRecipes();
            modal.style.display = 'none';
            recipeForm.reset();
        })
        .catch(error => console.error('Ошибка:', error));
    };

    document.getElementById('searchInput').addEventListener('input', () => {
        currentPage = 1;
        displayRecipes();
    });

    loadRecipes();
}); 