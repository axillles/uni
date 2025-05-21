import { BehaviorSubject, fromEvent, merge, combineLatest } from 'rxjs';
import { ajax } from 'rxjs/ajax';
import { map, switchMap, tap, filter, startWith, debounceTime } from 'rxjs/operators';

document.addEventListener('DOMContentLoaded', () => {
    const recipesList = document.getElementById('recipesList');
    const modal = document.getElementById('recipeModal');
    const addRecipeBtn = document.getElementById('addRecipeBtn');
    const closeBtn = document.querySelector('.close');
    const recipeForm = document.getElementById('recipeForm');
    const searchInput = document.getElementById('searchInput');
    const sortSelect = document.getElementById('sortSelect');
    const pagination = document.getElementById('pagination');

    let editingRecipeId = null;
    const PAGE_SIZE = 3;
    const page$ = new BehaviorSubject(1);
    const recipes$ = new BehaviorSubject([]);

    function renderRecipes(recipes, page, totalPages) {
        recipesList.innerHTML = recipes.map(recipe => `
            <div class="recipe-card" data-id="${recipe.id}">
                <div class="recipe-header">
                    <h2>${recipe.title}</h2>
                    <div class="recipe-actions">
                        <button class="edit-btn" data-edit="${recipe.id}">✎</button>
                        <button class="delete-btn" data-delete="${recipe.id}">✖</button>
                    </div>
                </div>
                <p><strong>Ингредиенты:</strong> ${recipe.ingredients.join(', ')}</p>
                <p><strong>Инструкция:</strong> ${recipe.instructions}</p>
                <p><strong>Время приготовления:</strong> ${recipe.cookingTime}</p>
            </div>
        `).join('');
        let pagBtns = '';
        for (let i = 1; i <= totalPages; i++) {
            pagBtns += `<button class="page-btn" data-page="${i}" style="${i===page?'font-weight:bold;':''}">${i}</button>`;
        }
        pagination.innerHTML = pagBtns;
    }

    function fetchRecipes() {
        ajax.getJSON('/api/recipes?_=' + Date.now()).subscribe(recipes => {
            recipes$.next(recipes);
        });
    }

    fetchRecipes();

    fromEvent(addRecipeBtn, 'click').subscribe(() => {
        editingRecipeId = null;
        recipeForm.reset();
        modal.style.display = 'block';
    });

    merge(
        fromEvent(closeBtn, 'click'),
        fromEvent(modal, 'click').pipe(filter(e => e.target === modal))
    ).subscribe(() => {
        modal.style.display = 'none';
    });

    const search$ = fromEvent(searchInput, 'input').pipe(
        map(e => e.target.value),
        debounceTime(200),
        startWith('')
    );
    const sort$ = fromEvent(sortSelect, 'change').pipe(
        map(e => e.target.value),
        startWith(sortSelect.value)
    );

    fromEvent(pagination, 'click').pipe(
        filter(e => e.target.matches('.page-btn')),
        map(e => parseInt(e.target.dataset.page)),
    ).subscribe(page => page$.next(page));

    combineLatest([
        recipes$,
        search$,
        sort$,
        page$
    ]).pipe(
        map(([recipes, search, sort, page]) => {
            let filtered = recipes.filter(r => r.title.toLowerCase().includes(search.toLowerCase()));
            filtered = filtered.sort((a, b) => sort === 'asc' ? a.title.localeCompare(b.title) : b.title.localeCompare(a.title));
            const totalPages = Math.max(1, Math.ceil(filtered.length / PAGE_SIZE));
            const paginated = filtered.slice((page-1)*PAGE_SIZE, page*PAGE_SIZE);
            return {recipes: paginated, page, totalPages};
        })
    ).subscribe(({recipes, page, totalPages}) => {
        renderRecipes(recipes, page, totalPages);
    });

    fromEvent(recipeForm, 'submit').pipe(
        tap(e => e.preventDefault()),
        map(() => ({
            title: document.getElementById('title').value,
            ingredients: document.getElementById('ingredients').value.split(',').map(i => i.trim()),
            instructions: document.getElementById('instructions').value,
            cookingTime: document.getElementById('cookingTime').value
        })),
        switchMap(recipeData => {
            const method = editingRecipeId ? 'PUT' : 'POST';
            const url = editingRecipeId ? `/api/recipes/${editingRecipeId}` : '/api/recipes';
            return ajax({
                url,
                method,
                headers: { 'Content-Type': 'application/json' },
                body: recipeData
            }).pipe(
                tap(() => {
                    modal.style.display = 'none';
                    recipeForm.reset();
                    page$.next(1);
                    editingRecipeId = null;
                }),
                tap(() => fetchRecipes())
            );
        })
    ).subscribe();

    fromEvent(recipesList, 'click').pipe(
        filter(e => e.target.matches('.edit-btn, .delete-btn')),
        tap(e => e.preventDefault()),
        map(e => ({
            type: e.target.classList.contains('edit-btn') ? 'edit' : 'delete',
            id: e.target.dataset.edit || e.target.dataset.delete
        })),
        switchMap(action => {
            if (action.type === 'edit') {
                editingRecipeId = action.id;
                return ajax.getJSON(`/api/recipes/${action.id}`).pipe(
                    tap(recipe => {
                        document.getElementById('title').value = recipe.title;
                        document.getElementById('ingredients').value = recipe.ingredients.join(', ');
                        document.getElementById('instructions').value = recipe.instructions;
                        document.getElementById('cookingTime').value = recipe.cookingTime;
                        modal.style.display = 'block';
                    }),
                    map(() => null)
                );
            } else if (action.type === 'delete') {
                if (confirm('Вы уверены, что хотите удалить этот рецепт?')) {
                    return ajax.delete(`/api/recipes/${action.id}`).pipe(
                        tap(() => {
                            page$.next(1);
                            editingRecipeId = null;
                        }),
                        tap(() => fetchRecipes())
                    );
                }
            }
            return [];
        })
    ).subscribe();
}); 