#ifndef ALGORITHM_INTERFACE_ABSTRACT_BANACH_SPACE_HH
#define ALGORITHM_INTERFACE_ABSTRACT_BANACH_SPACE_HH

#include <memory>
#include "abstractFunctionSpaceElement.hh"

namespace Algorithm
{
  namespace Interface
  {
    class AbstractScalarProduct;
    class AbstractNorm;

    static unsigned spaceIndex = 0;

    /**
     * @brief Abstract interface for banach spaces.
     */
    class AbstractBanachSpace
    {
    public:
      AbstractBanachSpace(std::shared_ptr<AbstractNorm> norm,
                          AbstractBanachSpace* dualSpace = nullptr);

      virtual ~AbstractBanachSpace() = default;

      void setNorm(std::shared_ptr<AbstractNorm> norm);

      const AbstractNorm& norm() const;

      std::shared_ptr<AbstractNorm> sharedNorm() const;

      std::unique_ptr<AbstractFunctionSpaceElement> element() const;

      unsigned index() const noexcept;

      void addPrimalSpace(const AbstractBanachSpace& primalSpace);

      void addDualSpace(const AbstractBanachSpace& dualSpace);

      bool isPrimalWRT(const AbstractBanachSpace& dualSpace) const;

      bool isDualWRT(const AbstractBanachSpace& primalSpace) const;

      const AbstractBanachSpace& dualSpace() const;

      AbstractBanachSpace* dualSpacePtr() const;

    protected:
      std::shared_ptr<AbstractNorm> norm_ = nullptr;
      virtual std::unique_ptr<AbstractFunctionSpaceElement> elementImpl() const = 0;

    private:
      std::vector<unsigned> primalSpaces_, dualSpaces_; ///< primal and dual spaces with respect to this space

      AbstractBanachSpace* dualSpace_ = nullptr;
      const unsigned index_ = spaceIndex++;
    };

    void makePrimalDual(AbstractBanachSpace& primalSpace, AbstractBanachSpace& dualSpace);
  }
}

#endif // ALGORITHM_INTERFACE_ABSTRACT_BANACH_SPACE_HH
