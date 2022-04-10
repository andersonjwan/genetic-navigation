from setuptools import Extension, setup
from Cython.Build import cythonize

extensions = [
    Extension(
        name="algorithmplusplus",
        sources=[
            "bindings/algorithmplusplus.pyx",
            "bindings/crossoverplusplus.pyx",
            "bindings/mutationplusplus.pyx",
            "bindings/optionsplusplus.pyx",
            "bindings/populationplusplus.pyx",
            "bindings/selectionplusplus.pyx",
            "bindings/individualplusplus.pyx"
        ],
        include_dirs=["src"]
    )
]

setup(
    name="py-genalg",
    version="0.0.1",
    ext_package="pygenalg",
    ext_modules=cythonize(extensions),
    python_requires=">=3.8"
)
